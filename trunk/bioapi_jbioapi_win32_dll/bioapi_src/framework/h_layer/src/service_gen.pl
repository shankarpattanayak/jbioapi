#-----------------------------------------------------------------------
# File: SERVICE_GEN.PL
#
# Copyright (c) 1999-2000 Intel Corporation. All rights reserved.
#-----------------------------------------------------------------------
#

use strict;
use lib ".";
use vars qw($ret %opts $debug $header @services $service
			$ret_type $call_conv $file_in $func_file $file_out
			$temp $fh $src %func_decls $template $func_name $node);
use Getopt::Std;
use Carp qw(carp cluck croak confess);
use File::Basename;
use FileHandle;
use C::Source;

# Get all the options.
#
$ret = getopts("hd:i:c:f:s:r:v:o:", \%opts);
if ($ret)
{
	if (exists($opts{h}))
	{
		err_msg("Please run perldoc " . basename($0) .
				" for documentation.");
		$ret = 0;
	}
}

if ($ret)
{
	$debug = $opts{d};
	if (!defined($debug))
	{
		$debug = 0;
	}
	else
	{
		if (($debug < 0) || ($debug > 2))
		{
			err_msg("Debug level \"$debug\" bad (0-2 are good values).");
			$ret = 0;
		}
	}

	$header = $opts{i};
	$header = "../../../include/bioapi_api.h" if (!defined($header));

	$file_in = $opts{c};

	$func_file = $opts{f};
	if (!defined($func_file))
	{
		err_msg("A function template file must be specified.");
		$ret = 0;
	}

#debug begin
	msg("function template is $func_file");
#debug end


	@services = split(/\s*,\s*/o, $opts{s});
	if (!@services)
	{
		err_msg("At least one service must be specified.");
		$ret = 0;
	}
	else
	{
		foreach $service (@services)
		{
			err_msg("\"$service\" is being checked.");
			if ($service !~ /^BIOAPI|DL|CL|HRS|TP|AC$/oi)
			{
				err_msg("\"$service\" is not a valid service.");
				$ret = 0;
				last;
			}

			$service = uc($service);
			err_msg("\"$service\" is the final value.");
		}
	}

	$ret_type = $opts{r};
	$ret_type = "BioAPI_RETURN" if (!defined($ret_type));

	$call_conv = $opts{v};
	$call_conv = "BioAPI" if (!defined($call_conv));

	$file_out = $opts{o};
}

undef(%opts);

if (!$ret)
{
	usage();
}
else
{
	msg("opening $header");

	$fh = new FileHandle($header);
	if (!defined($fh))
	{
		err_msg("could not open $header: $.");
		$ret = 0;
	}
	else
	{
		$src = new C::Source;
		if (!defined($src))
		{
			err_msg("could not create a C::Source object");
			$ret = 0;
		}
	}

	if ($ret)
	{
		%func_decls = ();

		err_msg("getting function declarations from $header");

		while (<$fh>)
		{
			$temp = $src->GetFuncDecls();
			if (!defined($temp))
			{
				err_msg("$header:$.: function declarations: " .
						$src->Error());
				$ret = 0;
			}
			else
			{
				while (($func_name, $node) = each(%$temp))
				{
					err_msg("$header:$.: $func_name: is being read");
					if (exists($func_decls{$func_name}))
					{
						err_msg("$header:$.: $func_name: redeclaration");
						$ret = 0;
					}
					else
					{
						$func_decls{$func_name} = $node;
					}
				}
			}

			last if (!$ret);
		}
		undef($src);

		if (!($fh->eof()))
		{
			err_msg("could not read all of $header");
			$ret = 0;
		}

		err_msg("closing $header");

		undef($fh);

		if ($ret && !%func_decls)
		{
			err_msg("$header: no function declarations");
			$ret = 0;
		}
	}

	if ($ret)
	{
		# Retrieve the function template.
		#

		msg("retrieving the function template");

		$template = get_function_template($func_file);

		if ((ref($template) ne "ARRAY") || (@$template == 0))
		{
			err_msg("function template retrieval failed");

			$ret = 0;
		}
	}

	if ($ret)
	{
		# Generate the file template.
		#

		msg("generating the service implementation from $file_in");

		$ret = service_gen(\%func_decls, $template, $file_in,
						   $ret_type, $call_conv, $file_out);

		err_msg("service implementation generation failed") if (!$ret);
	}
}

# Invert the meaning of the result code.
#

exit(!$ret);

############
# Functions
# ---------
#

# Name: get_function_template
# Description:
#	  Retrieves the function template from a file.
# Parameters:
#	  $func_file		- The file containing the function template.
# Return:
#	  A reference to an array containing the function template,
#	  with each even numbered element of the array containing
#	  straight text and odd numbered elements containing stuff
#	  to parse.
sub get_function_template($)
{
	my ($file) = shift;
	my ($array_ref, $fh, $src, $i, $lnum, $toBuff, $buff, $start,
		$symb, $line, $code, $codeSize, $token, $tokenSize, $col,
		$pcol, $lcol, $plcol, $lookOpen, $lookName, $lookParams,
		$done);

	$array_ref = [""];

	if (!defined($file))
	{
		err_msg("a function template file must be specified");

		undef($array_ref);
	}
	else
	{
		msg("opening $file");

		$fh = new FileHandle($file);

		if (!defined($fh))
		{
			undef($array_ref);
		}
		else
		{
			$src = new C::Source(noStrings=>1);
			undef($array_ref) if (!defined($src));
		}
	}

	if (defined($array_ref))
	{
		$lnum = 0;
		$toBuff = 0;
		$buff = "";
		$start = 0;
		$lookOpen = 1;
		$lookName = 0;
		$lookParams = 0;
		$done = 0;

		msg("reading $file");

		while (<$fh>)
		{
			$line = $_;

			$code = $src->GetCode($line);
			$codeSize = length($code);

			if (!$toBuff && ($code !~ /\S/o))
			{
				$array_ref->[$lnum] .= $line;
				next;
			}

			$pcol = 0;
			$plcol = 0;

			while ($ret && (($token = $src->GetToken($code)) ne ""))
			{
				$tokenSize = length($token);
				$col = $src->TokenIndex();

				$i = $col + $tokenSize;
				while ($ret && ($lcol = $src->LineIndex($i)) < 0)
				{
					if ($i < $codeSize)
					{
						$i++;
					}
					else
					{
						err_msg("$file:$.: went off the line");
						$ret = 0;
						last;
					}
				}

				if ($lookOpen)
				{
					if ($token eq '$')
					{
						$lookOpen = 0;
						$lookName = 1;

						$symb = $token;

						$toBuff = 1;
						$start = 1;
					}
				}
				elsif ($lookName)
				{
					if ($token =~
						/^(FUNC_DEF|FUNC_NAME|SERVICE|PARAMS)$/io)
					{
						msg("$file:$.: found $token");

						$symb .= $1;

						$lookName = 0;
						$lookParams = 1;
					}
					else
					{
						msg("could not find a symbol");

						$lookOpen = 1;
						$lookName = 0;
						$toBuff = 0;
					}
				}
				elsif ($lookParams)
				{
					if (($token eq ":") || ($token ne '$'))
					{
						$symb .= $token;
					}
					elsif ($token eq '$')
					{
						$lookOpen = 1;
						$lookParams = 0;

						$symb .= $token;

						$toBuff = 0;
						$done = 1;
					}
					else
					{
						$symb .= $token;
					}
				}

				# Erase the token from $code.
				#
				substr($code, $col, $tokenSize) =  " " x $tokenSize;

				if ($toBuff)
				{
					if ($start)
					{
						# Copy stuff from the end of the last symbol
						# up to just before this symbol.
						#
						$array_ref->[$lnum] .= substr($line, $plcol,
							$src->LineIndex($src->TokenIndex()) - $plcol);

						# Get just the symbol.
						#
						$buff = $token;

						$start = 0;
					}
					else
					{
						# Copy stuff from the end of the last symbol
						# and the current symbol.
						#
						$buff .= substr($line, $plcol,
										$lcol - $plcol);
					}
				}
				else
				{
					if (!$done)
					{
						if ($buff ne "")
						{
							# Empty the line buffer if necessary.
							#
							$array_ref->[$lnum] .= $buff;
							$buff = "";
						}

						# Copy stuff from the end of the last symbol
						# and the current symbol.
						#
						$array_ref->[$lnum] .= substr($line, $plcol,
													  $lcol - $plcol);
					}
					else
					{
						$lnum++;
						$array_ref->[$lnum] = $symb;

						$lnum++;
						$array_ref->[$lnum] = "";

						$buff = "";

						$done = 0;
					}
				}

				$pcol = $col;
				$plcol = $lcol;
			}

			# Take care of the end of the line.
			#
			if ($ret)
			{
				if ($toBuff)
				{
					$buff .= substr($line, $plcol);
				}
				else
				{
					$array_ref->[$lnum] .= substr($line, $plcol);
				}
			}
		}

		chomp($array_ref->[$lnum]);

		if (!($fh->eof()))
		{
			err_msg("could not read all of $file");
			$ret = 0;
		}

		msg("closing $file");

		undef($fh);
	}

	return $array_ref;
}

# Name: service_gen
# Description:
#	  Creates an implementation.
# Parameters:
#	  \%func_decls		- A reference to a function declaration hash.
#	  \@template		- The function template.
#	  $file_in			- The file to create the template from.
#	  $ret_type			- The return type to give to functions.
#	  $call_conv		- The calling convention to give to functions.
#	  $file_out			- The output file or undef (for STDOUT).
# Return:
#	  1					- The function completed successfully.
#	  0					- The function failed.
sub service_gen(\%\@$$$$)
{
	no strict 'refs';

	my ($func_decls) = shift;
	my ($template) = shift;
	my ($file_in) = shift;
	my ($ret_type) = shift;
	my ($call_conv) = shift;
	my ($file_out) = shift;
	my ($ret_type_size, $call_conv_size, $hIn, $hOut, $src,
		$line, $token, $tokenSize, $linebuff, $toLineBuff, $code,
		$codeSize, $start, $col, $pcol, $lcol, $plcol, $lookReturn,
		$lookCall, $lookName, $funcName, $lookParams, $parambuff,
		@params, $n, $i, $lookBlock, $depth, $done);
	my ($ret, %unknown) = (1, ());

	if (ref($func_decls) ne "HASH")
	{
		err_msg("a valid function declaration hash is required");
		$ret = 0;
	}
	else
	{
		if (ref($template) ne "ARRAY")
		{
			err_msg("a valid function template array is required");
			$ret = 0;
		}
	}

	if ($ret)
	{
		$ret_type_size = length($ret_type);
		if (!$ret_type_size || ($ret_type !~ /^\w+$/o))
		{
			err_msg("a valid calling convention must be specified");
			$ret = 0;
		}
	}

	if ($ret)
	{
		$call_conv_size = length($call_conv);
		if (!$call_conv_size || ($call_conv !~ /^\w+$/o))
		{
			err_msg("a valid calling convention must be specified");
			$ret = 0;
		}
	}

	if ($ret)
	{
		# Fill %unknown with the functions we expect to define.
		#
		while (($funcName, $n) = each(%$func_decls))
		{
			$unknown{$funcName} = 1;
		}

		if (defined($file_in))
		{
			msg("opening $file_in");

			$hIn = new FileHandle($file_in);
		}
		else
		{
			msg("taking the implementation from stdin");

			$hIn = "STDIN";
		}

		if (!defined($hIn))
		{
			err_msg("could not open $file_in: $!");
			$ret = 0;
		}
		else
		{
			if (defined($file_out))
			{
				msg("creating $file_out");

				$hOut = new FileHandle(">$file_out");
			}
			else
			{
				msg("outputting to stdout");

				$hOut = "STDOUT";
			}

			if (!defined($hOut))
			{
				err_msg("could not create $file_out: $!");
				$ret = 0;
			}
			else
			{
				$src = new C::Source(noStrings=>1);
				if (!defined($src))
				{
					err_msg("could not create a C::Source object");
					$ret = 0;
				}
			}
		}
	}

	if ($ret)
	{
		msg("reading $file_in");

		$linebuff = "";
		$toLineBuff = 0;
		$code = "";
		$start = 0;
		$lookReturn = 1;
		$lookCall = 0;
		$lookName = 0;
		$lookParams = 0;
		$lookBlock = 0;
		$depth = 0;
		$done = 0;

		# Iterate over all the lines of the file.
		#
		while (<$hIn>)
		{
			# This function definition replacement algorithm locates
			# any function definitions matching $ret_type $call_conv,
			# and a name from $func_decls.

			$line = $_;

			$code = $src->GetCode($line);
			$codeSize = length($code);

			if (!$toLineBuff &&
				(($code !~ /\S/o) || ($code =~ /^\#/o)))
			{
				print $hOut $line;
				next;
			}

			$pcol = 0;
			$plcol = 0;

			while ($ret && (($token = $src->GetToken($code)) ne ""))
			{
				$tokenSize = length($token);
				$col = $src->TokenIndex();

				$i = $col + $tokenSize;
				while ($ret && ($lcol = $src->LineIndex($i)) < 0)
				{
					if ($i < $codeSize)
					{
						$i++;
					}
					else
					{
						err_msg("$file_in:$.: went off the line");
						$ret = 0;
						last;
					}
				}

				if ($lookReturn)
				{
					if ($token eq $ret_type)
					{
						msg("$file_in:$.: found the return type");

						$lookReturn = 0;
						$lookCall = 1;

						$toLineBuff = 1;
						$start = 1;
					}
				}
				elsif ($lookCall)
				{
					if ($token eq $call_conv)
					{
						msg("$file_in:$.: found the calling convention");

						$lookCall = 0;
						$lookName = 1;
					}
					else
					{
						msg("$file_in:$.: could not find the calling convention");

						$lookReturn = 1;
						$lookCall = 0;
						$toLineBuff = 0;
					}
				}
				elsif ($lookName)
				{
					if (exists($func_decls->{$token}))
					{
						msg("$file_in:$.: found $token");

						$lookName = 0;
						$lookParams = 1;
						$funcName = $token;
						$depth = 0;
					}
					else
					{
						$lookReturn = 1;
						$lookName = 0;
						$toLineBuff = 0;
					}
				}
				elsif ($lookParams)
				{
					if ($token eq "(")
					{
						$depth++;
						$parambuff = "";
					}
					elsif ($token eq ")")
					{
						if ($depth == 1)
						{
							$lookParams = 0;
							$lookBlock = 1;
							$depth--;

							# Process the parameters.
							#
							$parambuff =~ s/^\s+//o;
							$parambuff =~ s/\s+$//o;
							@params = split(/\s*,\s*/o, $parambuff);

							if (@params !=
								@{$func_decls->{$funcName}{params}})
							{
								err_msg("$file_in:$.: $funcName: " .
										"number of parameters mismatch");
							}
							else
							{
								# A little minimum calculation.
								#
								$n = @{$func_decls->{$funcName}{params}} >
									 @params ? @params :
									 @{$func_decls->{$funcName}{params}};
								for ($i = 0; $i < $n; $i++)
								{
									if ($params[$i] ne
										${$func_decls->{$funcName}{params}}[$i])
									{
										err_msg("$file_in: $funcName: " .
												"parameter " . ($i + 1) .
												" mismatch");
									}
								}
							}
						}
						else
						{
							err_msg("$file_in:$.: parenthesis problem");
							$ret = 0;
						}
					}
					elsif ($depth == 1)
					{
						$parambuff .= " " if ($parambuff ne "");
						$parambuff .= $token;
					}
					elsif ($depth)
					{
						err_msg("$file_in:$.: parenthesis problem");
						$ret = 0;
					}
				}
				elsif ($lookBlock)
				{
					if ($token eq "{")
					{
						$depth++;
					}
					elsif ($token eq "}")
					{
						$depth--;

						if (!$depth)
						{
							$lookReturn = 1;
							$lookBlock = 0;

							$ret = interpolate_func($hOut,
								$template, $funcName,
								$func_decls->{$funcName}{params});

							$toLineBuff = 0;

							if ($ret)
							{
								msg("$file_in:$.: implemented $funcName");
								delete($unknown{$funcName});
								$done = 1;
							}
							else
							{
								err_msg("$file_in:$.: $funcName: " .
										"could not generate");
							}
						}
					}
					elsif (!$depth)
					{
						if ($token eq ";")
						{
							$lookReturn = 1;
							$lookBlock = 0;

							print $hOut "$ret_type $call_conv ",
								"$funcName(",
								join("\n," .
									 (" " x (length($funcName) + 1)),
									 @{$func_decls->{$funcName}{params}}),
								");";

							$toLineBuff = 0;
							$done = 1;
						}
						else
						{
							$lookReturn = 1;
							$lookBlock = 0;
							$toLineBuff = 0;
						}
					}
				}

				# Erase the token from $code.
				#
				substr($code, $col, $tokenSize) =  " " x $tokenSize;

				if ($toLineBuff)
				{
					if ($start)
					{
						# Copy stuff from the end of the last symbol
						# up to just before this symbol.
						#
						print $hOut substr($line, $plcol,
							$src->LineIndex($src->TokenIndex()) - $plcol);

						# Get just the symbol.
						#
						$linebuff = $token;

						$start = 0;
					}
					else
					{
						# Copy stuff from the end of the last symbol
						# and the current symbol.
						#
						$linebuff .= substr($line, $plcol,
											$lcol - $plcol);
					}
				}
				else
				{
					if (!$done)
					{
						if ($linebuff ne "")
						{
							# Empty the line buffer if necessary.
							#
							print $hOut $linebuff;
							$linebuff = "";
						}

						# Print out the stuff after the last symbol
						# and the current symbol.
						#
						print $hOut substr($line, $plcol,
										   $lcol - $plcol);
					}
					else
					{
						$linebuff = "";

						$done = 0;
					}
				}

				$pcol = $col;
				$plcol = $lcol;
			}

			# Take care of the end of the line.
			#
			if ($ret)
			{
				if ($toLineBuff)
				{
					$linebuff .= substr($line, $plcol);
				}
				else
				{
					print $hOut substr($line, $plcol);
				}
			}

			last if (!$ret);
		}

		if (!($hIn->eof()))
		{
			err_msg("could not read all of $file_in");
			$ret = 0;
		}

		msg("closing $file_out") if (defined($file_out));

		undef($hOut);

		msg("closing $file_in");

		undef($hIn);

		if ($ret)
		{
			# Check %unknown for function not defined.
			#
			while (($funcName, $n) = each(%unknown))
			{
				err_msg("$funcName: not found in $file_in");
				$ret = 0 if ($ret);
			}
		}
	}

	return $ret;
}

# Name: interpolate_func
# Description:
#	  Prints out a function template to the supplied file handle.
#	  Each symbol is interpolated.
# Parameters:
#	  $handle			- The handle to output the function to.
#	  $template			- The function template.
#	  $name				- The function's name.
#	  $parameters		- The function's parameters.
# Return:
#	  1					- The function completed successfully.
#	  0					- The function failed.
sub interpolate_func($\@$\@)
{
	no strict 'refs';

	my ($fh) = shift;
	my ($template) = shift;
	my ($funcName) = shift;
	my ($funcParams) = shift;
	my ($ret) = 1;
	my ($n, $i, $offset, $interp, $symb, $type, @params, $param, $index,
		$strip, $types, $indent, $value, $select, $match, $match_yes,
		@use);

	if (!defined($fh) || (ref($template) ne "ARRAY") ||
		!defined($funcName) || (ref($funcParams) ne "ARRAY"))
	{
		err_msg("invalid input");
		$ret = 0;
	}
	else
	{
		$n = @$template;
		$offset = 0;

		for ($i = 0; $ret && ($i < $n); $i++)
		{
			if ($i % 2)
			{
				$symb = $template->[$i];

				if ($symb =~ /^\$(\w+)\$$/o)
				{
					$type = $1;
					@params = ();
				}
				elsif ($symb =~ /^\$(\w+):([^\$]+)\$$/o)
				{
					$type = $1;
					@params = split(/,/o, $2);
				}
				else
				{
					err_msg("malformed template");
					$ret = 0;
				}

				if ($ret)
				{
					if (uc($type) eq "FUNC_NAME")
					{
						$index = 0;
						$strip = 0;

						foreach $param (@params)
						{
							if ($param =~ /^index=(\d+)$/io)
							{
								$index = $1;
							}
							elsif ($param =~ /^strip=(\d+)$/io)
							{
								$strip = $1;
							}
							else
							{
								err_msg("$param: invalid FUNC_NAME " .
										"parameter");
							}
						}

						$interp = substr($funcName, 0, $index);
						$interp .= substr($funcName, $index + $strip);
					}
					elsif (uc($type) eq "SERVICE")
					{
						# Assumes CSSM_SS
						#
						$interp = substr($funcName, 5, 2);
					}
					elsif (uc($type) eq "PARAMS")
					{
						$types = 0;
						$indent = $offset;
						$select = undef;
						$match = "";
						$match_yes = "";

						foreach $param (@params)
						{
							if ($param =~ /^types=(\w)/io)
							{
								if ((lc($1) eq "y") || (lc($1) eq "t"))
								{
									$types = 1;
								}
								else
								{
									$types = 0;
								}
							}
							elsif ($param =~ /^indent=(\d+)$/io)
							{
								$indent = $1;
							}
							elsif ($param =~ /^select=(\d+)$/io)
							{
								$select = $1;
							}
							elsif ($param =~ /^match=(\w+)\?(.+)$/io)
							{
								$match = $1;
								$match_yes = $2;
							}
							else
							{
								err_msg("$param: invalid PARAMS " .
										"parameter");
							}
						}

						if ($types && $match ne "")
						{
							err_msg("$funcName: turning parameter " .
									"types on conflicts with matching");
							$types = 0;
							$ret = 0;
						}

						if ($ret)
						{
							@use = ();

							if (defined($select))
							{
								if (!defined($funcParams->[$select - 1]))
								{
									err_msg("$funcName: parameter " .
											"$select does not exist");
								}
								else
								{
									push (@use,
										  $funcParams->[$select - 1]);
								}
							}

							if (!@use)
							{
								@use = @$funcParams;
							}

							if (!$types)
							{
								foreach $value (@use)
								{
									$value =~ /(\w+)$/o;
									$value = $1;
									if ($value eq $match)
									{
										$value = $match_yes;
									}
								}
							}
							else
							{
								foreach $value (@use)
								{
									$value =~ s/\*\s/\*/go;
								}
							}

							if (@use == 1)
							{
								$interp = $use[0];
							}
							else
							{
								$interp = join(",\n" . (" " x $indent),
											   @use);
							}
						}
					}
					else
					{
						err_msg("unknown function template type '$type'");
						$ret = 0;
					}
				}

				if ($ret)
				{
					print $fh $interp;

					$value = rindex($interp, "\n");
					if ($value < 0)
					{
						$offset += length($interp);
					}
					else
					{
						$offset = length($interp) - $value - 1;
					}
				}
			}
			else
			{
				print $fh $template->[$i];

				$value = rindex($template->[$i], "\n");
				if ($value < 0)
				{
					$offset += length($template->[$i]);
				}
				else
				{
					$offset = length($template->[$i]) - $value - 1;
				}
			}
		}
	}

	return $ret;
}

# Name: msg
# Description:
#	  Outputs a message with an optional file and line number.
#	  This is like warn() and carp(), except that this function
#	  formats output differently.
# Parameters:
#	  $msg				- The message.
#	  $fh				- An optional file handle to send the output to.
# Globals:
#	  $debug			- The debug level.
# Return:
#	  1					- The function completed successfully.
#	  0					- The function failed.
sub msg($;$)
{
	no strict 'refs';

	my ($msg) = shift;
	my ($fh) = shift;
	my ($ret) = 1;

	if (!defined($debug) || ($debug < 0) || ($debug > 2))
	{
		$debug = 1;
	}

	if (!defined($msg))
	{
		$ret = 0;
	}
	else
	{
		if (!defined($fh))
		{
			$fh = "STDOUT";
		}
	}

	if (!$ret)
	{
		cluck("invalid parameters");
	}
	else
	{
		if ($debug == 1)
		{
			chomp($msg);
			print $fh "$msg\n";
		}
		elsif ($debug == 2)
		{
			chomp($msg);
			cluck("$msg\n");
		}
	}

	return $ret;
}

# Name: err_msg
# Description:
#	  Outputs an error message.
# Parameters:
#	  $msg				- The message.
# Globals:
#	  $debug			- The debug level.
# Return:
#	  1					- The function completed successfully.
#	  0					- The function failed.
sub err_msg($)
{
	my ($msg) = shift;
	my ($ret, $fh, $value) = (1, "STDERR", $debug);

	$debug = 1 if (!defined($debug) || !$debug);

	$ret = msg($msg, $fh);

	$debug = $value;

	return $ret;
}

# Name: usage
# Description:
#	  Outputs the usage statement.
# Parameters:
#	  none
# Return:
#	  1					- The function completed successfully.
#	  0					- The function failed.
sub usage()
{
	my ($name) = basename($0);

	return err_msg("Usage:\n$name -h | " .
				   "[-d level] [-i header_ref] [-c input_file]\n" .
				   " " x (length($name) + 1) .
				   "-f function_template -s service[,service ...]\n" .
				   " " x (length($name) + 1) .
				   "[-r return_type] [-v calling_convention]\n" .
				   " " x (length($name) + 1) .
				   "[-o output_file]\n");
}

#
# -------------
# End Functions
################

__END__
# Documentation for service_gen.

=head1 NAME

service_gen - Create an implementation of CSSM DL, CL, TP, AC, or HRS APIs.

=head1 SYNOPSIS

B<service_gen> B<-h> | [B<-d> level] [B<-i> F<header_ref>]
[B<-c> F<input_file>] B<-f> F<function_template>
B<-s> service[,service ...] [B<-r> return_type]
[B<-v> calling_convention] [B<-o> F<output_file>]

=head1 DESCRIPTION

B<service_gen> generates the implementation of CSSM DL,
CL, TP, AC and HRS APIs.  It takes an existing implementation,
a header file as a reference, a function template,
and a list of services to create the implementation.

=head1 OPTIONS

=over 4

=item B<-h>

Prints the help message.  Using this option causes all
other options to be ignored.

=item B<-d> level

An optional parameter to set the debug level.  0 indicates
no debug messages, 1 turns them on, and 2 turns them on
with stack tracing.	 The default is 0.

=item B<-i> F<header_ref>

This optional parameter sets the file to use as the
authorative source of function declarations.  The default is
../../../include/bioapi_api.h

=item B<-c> F<input_file>

An optional parameter to set a file to use as the source of
function definitions to replace.  The default is the
standard input.

=item B<-f> F<function_template>

A file containing the function to interpolate and implement.
Interpolated variables are enclosed in dollar symbols.	The
following are the currently supported variables:

	$FUNC_NAME:[index=num]:num is a natural number:default=0,
			   [strip=num]:num is a counting number:default=0$

	This will be replaced with the name of the function
	being implemented.	The index parameter indicates where
	in the name (0 for the first character) to start doing
	some operation.	 Currently, only strip is supported.
	The strip parameter indicates how many characters to
	remove.

	$SERVICE$

	The interpolated value will be the module name (DL, CL,
	TP, AC,HRS or BIOAPI).

	$PARAMS:[types=(y|yes|true)|(n|no|false)]:default=no,
			[indent=num]:num is a number:default=current location,
			[select=num]:num is a positive number:default=all,
			[match=str?yes_str]:implies types=no$

	This will be replaced with the function's paramters.
	The types paramter specifies whether to include the
	type for each parameter.  The indent parameter allows
	the setting of the indent for each function parameter
	that wraps (function parameter 2 and on).  The select
	parameter allows for the interpolation of just one of
	the function's parameters (1 being the first).	And
	finally, the match parameter allows for simple string
	replacement.  If the parameter's name matches the
	string, it is replaced with the yes string.	 Otherwise,
	it is left as is.

=item B<-s> service[,service ...]

The list of one or more services to implement.	A service
is one of DL, CL, TP, AC, HRS, or BIOAPI.

=item B<-r> return_type

An optional parameter to set the return type to use to double
check the current implementation against.  The default is CSSM_RETURN.

=item B<-v> calling_convention

An optional parameter to set the calling convention to use to
double check the current implementation against.  The default is
CSSMAPI.

=item B<-o> F<output_file>

An optional parameter to set the file in which to write the new
implementation.	 The default is the standard output.

=back

=head1 VERSION

1.0

=head1 AUTHOR

Patrick Ryan,
Intel Technical Intern,
Security Technology Laboratory,
Intel Architecture Laboratories

=cut

