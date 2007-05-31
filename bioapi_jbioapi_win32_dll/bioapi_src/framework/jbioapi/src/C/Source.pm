#-----------------------------------------------------------------------
# File: SOURCE.PM
#
# Copyright (c) 1999-2000 Intel Corporation. All rights reserved.
#-----------------------------------------------------------------------
#

package C::Source;

use strict;
use vars qw($VERSION @ISA @EXPORT @EXPORT_OK);

require Exporter;
require 5.003;

@ISA = qw(Exporter);
# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.
@EXPORT = qw(
	
);
$VERSION = '1.0';

# Methods go here.

# Name: new
# Description:
#	  Creates a new object, or copies an existing object.
# Parameters:
#	  The parameters are passed in as a hash.  Here's an example:
#	  $src = new C::Source(noStrings=>0, isComment=>0);
#
#	  noStrings	  (opt) - Whether to filter out strings.
#	  isComment	  (opt) - The source is currently in a comment.
#	  isString	  (opt) - The source is currently in a string.
#	  tokenIndex  (opt) - The index of the last token.
# State:
#	  $_noStrings		- Whether to filter out strings.
#	  $_isComment		- Whether the source is currently in a comment.
#	  $_isString		- Whether the source is currently in a string.
#	  $_codeRegions		- Code region indecies from last GetCode().
#	  $_tokenIndex		- The index of the last token.
#	  $_tokenSize		- The size of the last token.
#	  $_funcDecl		- A buffer to store intermediate strings.
#	  $_errString		- Contains a string describing an internal error.
# Return:
#	  A reference to the new object, or undef on error.
sub new($;%)
{
	my ($self) = shift;
	my ($class) = ref($self) || $self;
	my (%params) = @_;
	my ($obj, $param, $value);

	if (ref($self))
	{
		# Copy the object.
		#

		if (ref($self) ne "HASH"		   ||
			!exists($self->{_noStrings})   ||
			!exists($self->{_isComment})   ||
			!exists($self->{_isString})	   ||
			!exists($self->{_codeRegions}) ||
			!exists($self->{_tokenIndex})  ||
			!exists($self->{_tokenSize})   ||
			!exists($self->{_funcDecl})	   ||
			!exists($self->{_errString})	 )
		{
			# Bad object, don't copy.
			#
			undef($obj);
		}
		else
		{
			# Make a copy.
			#
			$obj = {_noStrings	 => $self->{_noStrings},
					_isComment	 => $self->{_isComment},
					_isString	 => $self->{_isString},
					_codeRegions => $self->{_codeRegions},
					_tokenIndex	 => $self->{_tokenIndex},
					_tokenSize	 => $self->{_tokenSize},
					_funcDecl	 => $self->{_funcDecl},
					_errString	 => $self->{_errString} };
		}
	}
	else
	{
		# Create a new object.
		#

		$obj = {_noStrings	 => 0,
				_isComment	 => 0,
				_isString	 => 0,
				_codeRegions => undef,
				_tokenIndex	 => 0,
				_tokenSize	 => 0,
				_funcDecl	 => "",
				_errString	 => "" };
	}

	if (ref($obj))
	{
		while (ref($obj) && (($param, $value) = each(%params)))
		{
			if ($param =~ /^noStrings$/io)
			{
				$obj->{_noStrings} = 1 if ($value);
			}
			elsif ($param =~ /^isComment$/io)
			{
				$obj->{_isComment} = 1 if ($value);
			}
			elsif ($param =~ /^isString$/io)
			{
				$obj->{_isString} = 1 if ($value);
			}
			elsif ($param =~ /^tokenIndex$/io)
			{
				$value -= $[;

				if ($value < 0)
				{
					undef($obj);
				}
				else
				{
					$obj->{_tokenIndex} = $value;
				}
			}
			else
			{
				undef($obj);
			}
		}
	}

	# Make the hash reference an instance of this class.
	#
	bless($obj, $class) if (ref($obj));

	return $obj;
}

# Name: GetCode
# Description:
#	  Gets the code from a line, replacing comments with a space to
#	  prevent merging two tokens together, if necessary, and emptying
#	  strings.	Since this also strips out C++ style comments, it
#	  assumes that it was given a line from a file, with the delimiter
#	  being $/.
# Parameters:
#	  $line		  (opt) - A line of C/C++ source.
# State:
#	  $_codeRegions		- Code region indecies from last GetCode().
# Return:
#	  The code from $line, or undef on error.
sub GetCode($;$)
{
	my ($self) = shift;
	my ($line, $eol, $ooff, $coff, $cseg, $loff, $col, @inerts);
	local ($[) = 0;
	my ($code) = "";

	undef($code) if (!ref($self));

	if (defined($code))
	{
		$line = @_ ? shift : $_;
		if (!defined($line))
		{
			$self->Error("no line given as parameter or in \$_");
			undef($code);
		}
	}

	if (defined($code))
	{
		# If there is a delimiter ($/, usually "\n") at the end
		# of the string, get rid of them, but remember how many
		# there were, so they can be restored later.
		#
		$eol = chomp($line);

		# This contains a mapping of code offsets to
		# line offsets.	 The idea is to be able to reconstruct
		# offsets into $line based on offsets of the string
		# returned from this method.  A separate method will
		# take care of the reconstruction.
		#
		$self->{_codeRegions} = {0=>0};

		$ooff = 0; # The current offset into the original line.
		$coff = 0; # The current offset into the code.
		# $cseg is the size of the code segment to be copied to $code.
		# $loff is the offset into the current line to start reading.

		# Erase any comments from the line, ignoring any
		# comments embedded in strings.
		#
		while ($line ne "")
		{
			if ($self->IsComment())
			{
				$col = index($line, "*/");
				if ($col < 0)
				{
					# The comment continues.
					#
					$cseg = 0;
					$loff = length($line);
				}
				else
				{
					$cseg = 0;
					$loff = $col + 2;

					# The comment ends.
					#
					if ($code =~ /\S$/o &&
						(substr($line, $col + 2, 1) =~ /\S/))
					{
						# There is non-whitespace at the end of $code,
						# so a space should be inserted to protect from
						# merging two tokens together.
						#
						$code .= " ";

						# Create a hole.
						#
						$self->{_codeRegions}{$coff} = -1;

						$coff++;
					}

					# Create a new code region.
					#
					$self->{_codeRegions}{$coff} = $ooff + $loff;

					$self->IsComment(0);
				}
			}
			elsif ($self->IsString())
			{
				$col = index($line, "\"");
				if ($col < 0)
				{
					# No end in sight for the string.
					#
					$loff = length($line);
					$cseg = $self->NoStrings() ? 0 : $loff;
				}
				else
				{
					if ($col && (substr($line, $col - 1, 1) eq "\\"))
					{
						# The string continues (backslash).
						#
						$cseg = $self->NoStrings() ? 0 : $col;

						$loff = $col + 1;
					}
					else
					{
						# The string ends (no backslash).
						#

						$loff = $col + 1;

						if ($self->NoStrings())
						{
							$code .= "\"";
							$cseg = 0;

							$self->{_codeRegions}{$coff} = $ooff + $col;

							$coff++;
						}
						else
						{
							$cseg = $col + 1;
						}

						$self->IsString(0);
					}
				}
			}
			else
			{
				# The current position isn't a comment (C or C++)
				# or a part of a string.  Move everything up
				# to the start of a comment or a string
				# and to $code.	 If there is a comment starting
				# or a string starting, set the appropriate flags.

				@inerts = ({type=>"c", col=>index($line, "/*")},
						   {type=>"p", col=>index($line, "//")},
						   {type=>"s", col=>index($line, "\"")});
				@inerts = sort {$a->{col} <=> $b->{col}} @inerts;

				# Remove ones that aren't in the line.
				#
				while (@inerts)
				{
					if ($inerts[0]->{col} < 0)
					{
						shift(@inerts);
					}
					else
					{
						last;
					}
				}

				if (!@inerts)
				{
					# There is nothing to strip from the line, so
					# it must be code.

					$cseg = length($line);		   # All to $code.
					$loff = $cseg;				   # Empty $line.
				}
				else
				{
					# The size of the code segment is this, plus
					# possibly a quote.
					#
					$cseg = $inerts[0]->{col};

					# Figure out how much to shave off the line.
					#
					if ($inerts[0]->{type} eq "c")
					{
						# C comment.
						#
						$loff = $cseg + 2;

						$self->IsComment(1);
					}
					elsif ($inerts[0]->{type} eq "p")
					{
						# C++ comment.
						#
						$loff = length($line);
					}
					else
					{
						# String.
						#
						$cseg++;
						$loff = $cseg;

						$self->IsString(1);
					}
				}
			}

			if ($cseg)
			{
				$code .= substr($line, 0, $cseg);
				$coff += $cseg;
			}

			if ($loff)
			{
				$line = substr($line, $loff);
				$ooff += $loff;
			}
		}

		# If there was an delimiter at the end of the line, restore
		# it.
		#
		if ($eol)
		{
			if (!defined($/) || ($/ eq ""))
			{
				$code .= "\n" x $eol;
			}
			else
			{
				$code .= $/ x $eol;
			}
		}
	}

	return $code;
}

# Name: NoStrings
# Description:
#	  Gets or sets whether the string filter is on.
# Parameters:
#	  noStrings	  (opt) - Whether to filter out strings.
# State:
#	  $_noStrings		- Whether to filter out strings.
# Return:
#	  0					- The string filter is off.
#	  1					- The string filter is on.
#	  undef				- An error occured.
sub NoStrings($;$)
{
	my ($self) = shift;
	my ($param) = shift;
	my ($ret) = 0;

	if (!ref($self))
	{
		undef($ret);
	}
	else
	{
		if (defined($param))
		{
			$self->{_noStrings} = $param ? 1 : 0;
		}

		$ret = $self->{_noStrings};
	}

	return $ret;
}

# Name: IsComment
# Description:
#	  Gets or sets whether the source is currently in a comment.
# Parameters:
#	  isComment	  (opt) - Whether the source is currently in a comment.
# State:
#	  $_isComment		- Whether the source is currently in a comment.
# Return:
#	  0					- The source is not currently in a comment.
#	  1					- The source is currently in a comment.
#	  undef				- An error occured.
sub IsComment($;$)
{
	my ($self) = shift;
	my ($param) = shift;
	my ($ret) = 0;

	if (!ref($self))
	{
		undef($ret);
	}
	else
	{
		if (defined($param))
		{
			$self->{_isComment} = $param ? 1 : 0;
		}

		$ret = $self->{_isComment};
	}

	return $ret;
}

# Name: IsString
# Description:
#	  Gets or sets whether the source is currently in a string.
# Parameters:
#	  isString	  (opt) - Whether the source is currently in a string.
# State:
#	  $_isString		- Whether the source is currently in a string.
# Return:
#	  0					- The source is not currently in a string.
#	  1					- The source is currently in a string.
#	  undef				- An error occured.
sub IsString($;$)
{
	my ($self) = shift;
	my ($param) = shift;
	my ($ret) = 0;

	if (!ref($self))
	{
		undef($ret);
	}
	else
	{
		if (defined($param))
		{
			$self->{_isString} = $param ? 1 : 0;
		}

		$ret = $self->{_isString};
	}

	return $ret;
}

# Name: LineIndex
# Description:
#	  Given an index from the last string returned by
#	  C::Source::GetCode, the index into the original string is
#	  returned.	 If an index greater than the maximum code index
#	  is given, then the resulting index is not an index into the
#	  original string.
# Parameters:
#	  $cindex	  (opt) - A code index from the last GetCode().
# State:
#	  $_codeRegions		- Code region indecies from last GetCode().
# Return:
#	  The corresponding index into the last string passed to
#	  GetCode(), (with the base being $[), $[ - 1 if there is no
#	  mapping, or undef on error.
sub LineIndex($$)
{
	my ($self) = shift;
	my ($cindex) = shift;
	my ($ret) = -1;
	my ($codeRegion, $prevCodeRegion);

	undef($ret) if (!ref($self));

	if (defined($ret))
	{
		if (!defined($self->{_codeRegions}))
		{
			$self->Error("GetCode() must be called first");
			undef($ret);
		}
	}

	if (defined($ret))
	{
		# Convert the base to 0.
		#
		$cindex -= $[;

		# Order the hash keys in decending order and then
		# iterate through them.	 The first key to be equal or
		# smaller than the code index is the right code region.
		#
		foreach $codeRegion (sort({$b <=> $a}
								  keys(%{$self->{_codeRegions}})))
		{
			if ($cindex >= $codeRegion)
			{
				# Calculate the index into the line.
				#
				if ($self->{_codeRegions}{$codeRegion} < 0)
				{
					# The first element examined can not be
					# an invalid mapping, since invalid mappings
					# only occur between code regions.
					#
					$ret = $self->{_codeRegions}{$prevCodeRegion} +
						   ($cindex - $prevCodeRegion) + 1;
				}
				else
				{
					$ret = $self->{_codeRegions}{$codeRegion} +
						   ($cindex - $codeRegion);
				}

				last;
			}
			
			# Save the previous code region in case there is no
			# for the match.
			#
			$prevCodeRegion = $codeRegion;
		}

		# Convert the base back to $[;
		#
		$ret += $[;
	}

	return $ret;
}

# Name: GetToken
# Description:
#	  Looks at a string and returns the next token.	 If this is
#	  called in list contex, then a reference to an array of
#	  all the tokens is returned.  A token is defined as either 1)
#	  a string of the upper and lowercase letters, zero through 9,
#	  or an underscore, or 2) a single non-whitespace character not
#	  from the set given in (1).  This method remembers where it was
#	  in the string to get the next token.	That state is reset if the
#	  method is called with an undefined string, or if the string passed
#	  to the method does not have a location corresponding to the last
#	  location.
# Parameters:
#	  $str		  (opt) - The string.
# State:
#	  $_tokenIndex		- The index of the last token.
#	  $_tokenSize		- The size of the last token.
# Return:
#	  In scalar context, the value can be the token, "" for no token,
#	  or undef on reset or error.  In list conext, the value can be 0
#	  or more tokens.  Since there is no way to differentiate between
#	  an empty list and undefined, then error conditions are not
#	  easily communicated if called in list context.
sub GetToken($;$)
{
	my ($self) = shift;
	my ($ret, $str, $tok) = ("", "", "");
	local ($[) = 0;

	undef($ret) if (!ref($self));

	if (defined($ret))
	{
		$str = @_ ? shift : $_;
		if (!defined($str))
		{
			$self->{_tokenIndex} = 0;
			$self->{_tokenSize} = 0;
			undef($ret);
		}
	}

	if (defined($ret) && ($self->{_tokenIndex} < 0))
	{
		$self->Error("the token index is invalid");
		undef($ret);
	}

	if (defined($ret))
	{
		if (!wantarray())
		{
			$str = substr($str,
						  $self->{_tokenIndex} + $self->{_tokenSize});

			if ($str =~ s/^(\s+)//o)
			{
				$self->{_tokenIndex} += length($1);
			}

			if ($str eq "")
			{
				$ret = "";
				$self->{_tokenIndex} = 0;
				$self->{_tokenSize} = 0;
			}
			else
			{
				if ($str =~ /^(\w+)/o)
				{
					$ret = $1;
				}
				elsif ($str =~ /^([^\s\w])/o)
				{
					$ret = $1;
				}

				$self->{_tokenIndex} += $self->{_tokenSize};
				$self->{_tokenSize} = length($ret);
			}
		}
		else
		{
			$ret = [];

			for (;;)
			{
				$tok = $self->GetToken($str);

				if (!defined($tok))
				{
					$ret = [];
					last;
				}
				elsif ($tok eq "")
				{
					last;
				}
				else
				{
					push(@$ret, $tok);
				}
			}
		}
	}

	return ((wantarray()) ? @$ret : $ret);
}

# Name: TokenIndex
# Description:
#	  Gets the index of the last token or sets the index to look
#	  for the next token.
# Parameters:
#	  index		  (opt) - The index to look for the next token.
# State:
#	  $_tokenIndex		- The index of the last token.
#	  $_tokenSize		- The size of the last token.
# Return:
#	  The last token index or undef on error.
sub TokenIndex($;$)
{
	my ($self) = shift;
	my ($param) = shift;
	my ($ret) = 0;

	if (!ref($self))
	{
		undef($ret);
	}
	else
	{
		if (defined($param))
		{
			$param -= $[;

			if ($param < 0)
			{
				$self->Error("the token index is invalid");
				undef($ret);
			}
			else
			{
				$self->{_tokenIndex} = $param;
				$self->{_tokenSize} = 0;
			}
		}

		$ret = $self->{_tokenIndex} + $[ if (defined($ret));
	}

	return $ret;
}

# Name: GetFuncDecls
# Description:
#	  Given a line, any function declarations are extracted and
#	  returned.	 For any parts of the string left over, they are
#	  saved for the next invocation.  A hash reference is returned
#	  or undef on error.  The undef value can be passed to reset
#	  processing.
# Parameters:
#	  $line		  (opt) - A line of C/C++ source.
# State:
#	  $_funcDecl		- A buffer to store intermediate strings.
# Return:
#	  A reference to a symbol hash or undef on error.
#	  The key to the hash is the function name.	 The value of the
#	  hash is a reference to a hash containing the following:
#		  type			=> Type of symbol (i.e. "function").
#		  params		=> Reference to an array of the parameters.
sub GetFuncDecls($;$)
{
	my ($self) = shift;
	my ($ret, $line, $reset, $src,	$symbs) =
	   (1,	  undef, 0,		 undef, undef);
	my ($func_name, $params, $param, %node);

	$ret = 0 if (!ref($self));

	if ($ret)
	{
		$line = @_ ? shift : $_;
		if (!defined($line))
		{
			$self->{_funcDecl} = "";
			$reset = 1;
			$ret = 0;
		}
	}

	if ($ret)
	{
		$src = new C::Source(noStrings=>1);
		if (!defined($src))
		{
			$self->Error("could not create a C::Source object");
			$ret = 0;
		}
	}

	if ($ret)
	{
		$symbs = {};

		$line = $src->GetCode($line);
		if (!defined($line))
		{
			$self->Error("could not strip comments");
			$ret = 0;
		}
		else
		{
			$self->{_funcDecl} .= $line;

			while ($ret &&
				   ($self->{_funcDecl} =~ /(\w+)\s*\(([^)]*)\)\s*;/o))
			{
				# Found a function declaration.
				#
				$func_name = $1;
				$params = $2;
				$self->{_funcDecl} = $';

				# A function declaration has been retrieved.
				# Add it to %$symbs.
				#

				if (exists($symbs->{$func_name}))
				{
					$self->Error("$func_name duplicated");
					$ret = 0;
				}
				else
				{
					%node = ( type		=> "function",
							  params	=> []		   );
					foreach $param (split(/,/o, $params))
					{
						$param = join(" ", $src->GetToken($param));
						push(@{$node{params}}, $param) if ($param ne "");
					}

					$symbs->{$func_name} = \%node;
				}
			}
		}
	}

	if (!$ret)
	{
		$symbs = $reset ? {} : undef;
	}

	return $symbs;
}

# Name: Error
# Description:
#	  Gets or sets the last error generated by this object.	 Only
#	  the object itself should set the error.
# Parameters:
#	  errString	  (opt) - The error string.
# State:
#	  $_errString		- Contains a string describing an internal error.
# Return:
#	  The current error message or undef on error.
sub Error($;$)
{
	my ($self) = shift;
	my ($errString) = shift;
	my ($ret) = "";

	if (!ref($self))
	{
		undef($ret);
	}
	else
	{
		$self->{_errString} = $errString if (defined($errString));
		$ret = $self->{_errString};
	}

	return $ret;
}

1;
__END__
# Documentation for C::Source.

=head1 NAME

C::Source - Perl extension for C/C++ source parsing.

=head1 SYNOPSIS

  # Example Program
  # ---------------
  #
  # If the first argument is "-f", then the function declarations
  # are taken from STDIN and printed out.  Otherwise, just
  # comments are stripped from STDIN and the code is printed out.
  # It is assumed that STDIN is a stream of C/C++ source.

  use strict;
  use C::Source;
  use vars qw($get_fdecls $src $code $fdecls $name $node $fdecl $n);

  $get_fdecls = (lc($ARGV[0]) eq "-f") ? 1 : 0;

  $src = new C::Source();
  die "could not create a C::Source object\n" if (!defined($src));

  # Print out the source without C or C++ comments.
  #
  while (<STDIN>)
  {
	  if (!$get_fdecls)
	  {
		  $code = $src->GetCode();
		  die "$.: " . $src->Error() . "\n" if (!defined($code));
		  print $code;
	  }
	  else
	  {
		  $fdecls = $src->GetFuncDecls();
		  die "$.: " . $src->Error() . "\n" if (!defined($fdecls));

		  while (($name, $node) = each(%$fdecls))
		  {
			  if ($node->{type} ne "function")
			  {
				  die "$.: $name is not a function.\n";
			  }
			  else
			  {
				  $fdecl = "$name(";
				  $n = length($fdecl);
				  $fdecl .= join(",\n" . (" " x $n), @{$node->{params}});
				  $fdecl .= ");\n\n";

				  print $fdecl;
			  }
		  }
	  }
  }

=head1 DESCRIPTION

The C::Source extension is designed to provide C/C++ source manipulation.
Method Summary:

  C::Source::new
  --------------
  Description:
	  Creates a new object, or copies an existing object.
  Parameters:
	  The parameters are passed in as a hash.  Here's an example:
	  $src = new C::Source(noStrings=>0, isComment=>0);
 
	  noStrings	  (opt) - Whether to filter out strings.
	  isComment	  (opt) - The source is currently in a comment.
	  isString	  (opt) - The source is currently in a string.
	  tokenIndex  (opt) - The index of the last token.
  Return:
	  A reference to the new object, or undef on error.

  C::Source::GetCode
  ------------------
  Description:
	  Gets the code from a line, replacing comments with a space to
	  prevent merging two tokens together, if necessary, and emptying
	  strings.	Since this also strips out C++ style comments, it
	  assumes that it was given a line from a file, with the delimiter
	  being $/.
  Parameters:
	  $line		  (opt) - A line of C/C++ source.
  Return:
	 The code from $line, or undef on error.

  C::Source::NoStrings
  --------------------
  Description:
	  Gets or sets whether the string filter is on.
  Parameters:
	  noStrings	  (opt) - Whether to filter out strings.
  Return:
	  0					- The string filter is off.
	  1					- The string filter is on.
	  undef				- An error occured.

  C::Source::IsComment
  --------------------
  Description:
	  Gets or sets whether the source is currently in a comment.
  Parameters:
	  isComment	  (opt) - Whether the source is currently in a comment.
  Return:
	  0					- The source is not currently in a comment.
	  1					- The source is currently in a comment.
	  undef				- An error occured.

  C::Source::IsString
  -------------------
  Description:
	  Gets or sets whether the source is currently in a string.
  Parameters:
	  isString	  (opt) - Whether the source is currently in a string.
  Return:
	  0					- The source is not currently in a string.
	  1					- The source is currently in a string.
	  undef				- An error occured.

  C::Source::LineIndex
  --------------------
  Description:
	  Given an index from the last string returned by
	  C::Source::GetCode, the index into the original string is
	  returned.	 If an index greater than the maximum code index
	  is given, then the resulting index is not an index into the
	  original string.
  Parameters:
	  $cindex	  (opt) - A code index from the last GetCode().
  Return:
	  The corresponding index into the last string passed to
	  GetCode(), (with the base being $[), $[ - 1 if there is no
	  mapping, or undef on error.

  C::Source::GetToken
  -------------------
  Description:
	  Looks at a string and returns the next token.	 If this is
	  called in list contex, then a reference to an array of
	  all the tokens is returned.  A token is defined as either 1)
	  a string of the upper and lowercase letters, zero through 9,
	  or an underscore, or 2) a single non-whitespace character not
	  from the set given in (1).  This method remembers where it was
	  in the string to get the next token.	That state is reset if the
	  method is called with an undefined string, or if the string passed
	  to the method does not have a location corresponding to the last
	  location.
  Parameters:
	  $str		  (opt) - The string.
  Return:
	  In scalar context, the value can be the token, "" for no token,
	  or undef on reset or error.  In list conext, the value can be 0
	  or more tokens.  Since there is no way to differentiate between
	  an empty list and undefined, then error conditions are not
	  easily communicated if called in list context.

  C::Source::TokenIndex
  ---------------------
  Description:
	  Gets the index of the last token or sets the index to look
	  for the next token.
  Parameters:
	  index		  (opt) - The index to look for the next token.
  Return:
	  The last token index or undef on error.

  C::Source::GetFuncDecls
  -----------------------
  Description:
	  Given a line, any function declarations are extracted and
	  returned.	 For any parts of the string left over, they are
	  saved for the next invocation.  A hash reference is returned
	  or undef on error.  The undef value can be passed to reset
	  processing.
  Parameters:
	  $line		  (opt) - A line of C/C++ source.
  Return:
	  A reference to a symbol hash or undef on error.
	  The key to the hash is the function name.	 The value of the
	  hash is a reference to a hash containing the following:
		  type			=> Type of symbol (i.e. "function").
		  params		=> Reference to an array of the parameters.

  C::Source::Error
  ----------------
  Description:
	  Gets or sets the last error generated by this object.	 Only
	  the object itself should set the error.
  Parameters:
	  errString	  (opt) - The error string.
  Return:
	  The current error message or undef on error.

=head1 AUTHOR

Patrick G. Ryan, pgryan@geocities.com

=head1 VERSION

1.0

=head1 SEE ALSO

perl(1).

=cut
