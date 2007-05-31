#-----------------------------------------------------------------------
# File: TEMPLATE_PROC.PL
#
# Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
#-----------------------------------------------------------------------
#

###########################################################################
#
# SYNTAX: template_proc template_file [ pre-processor arguments ]
#  Only -Dname, -I, and -L arguments should be used.
#
# This script will process a template (.?tp) file and output a final
# human readable file that has been partially pre-processed. The
# resulting file has the same name as the template, with the first
# character of the template extension as its extension.
#
# A template file is a standard C file with two extra pre-processor
# directives: #process_start and #process_end. The #process_start
# directive indicates that the C pre-processor and pretty-printing routines
# should be run on the template file until the end-of-file or #process_end
# directive is found. The contents of the source located between the
# #process_start and #process_end directives must be independent of any
# other process blocks or any code located outside of the block.
#
# In the case where a function was defined, if FIRST_FUNC_PARAM appears in
# the body of the function, then it will be replaced with the first parameter
# of the function, or nothing in the case where there are no parameters.  If
# FUNC_NAME_AS_ERROR is seen, then it will be replaced with an error code
# made from the name of the function.
#
# If the macro-like symbol PREPROCESSOR_ERROR_DEFINE, it will be changed to a
# preprocessor definition of a symbol, taking three or four parameters.	 The
# first parameter is treated as a prefix to the definition.	 The second parameter
# is the string to translate to an error code like version of the string.
# The third paramter is the value to use as the base part, to which an offset will
# be added.	 If the fourth paramter is specified, it is a sequence identifier that
# will be used to track the offsets.  If it is not specified, a default sequence
# will be used.
#
# Pretty-print configuration may be used by placing an option name followed
# by a numeric value on the same line as the #process_start directive. A
# pretty-print setting is carried through the entire template file. If the
# template contains multiple sections to be processed, the settings only
# need to be specified for the first section, but they can be specified for
# each section. The recognized configuration parameters are as follows:
#
#	fnameindent	   Specifies the number of blanks to place before the first
#				   line of a function prototype. This includes funtion
#				   pointer type definitions.
#	fbodyindent	   Specifies the number of blanks to place before each
#				   statement inside the body of a function definition.
#	paramindent	   Specifies the number of blanks to plaec before each
#				   parameter of a function prototype or typedef. Each
#				   parameter is placed on a separate line.
#	funcptrindent  When a line starts with a function pointer type name,
#				   the line will be indented this number of blanks. The
#				   pointer type names are assumed to start with the pattern
#				   "_BioAPI_".
#	fptrnameindent This parameter indicates how many columns will precede
#				   the name of a function pointer variable. This parameter
#				   works in conjunction with funcptrindent. If the total of
#				   funptrindent+sizeof(ptr type name) <= fptrnameindent,
#				   then this parameter is ignored for the line and
#				   funcptrindent spaces are placed between the pointer type
#				   name and the variable name.
#
# Example formatting
#
# Function declaration or function pointer typdef:
# 0	   5	10	 15	  20   25	30	 35	  40   45	50	 55
# |	   |	|	 |	  |	   |	|	 |	  |	   |	|	 |
#		  BioAPI_RETURN BioAPI BioAPI_SomeFunc(
# |		 |						  uint32 Param1,
# |		 |						  uint32 Param2 );
# |		 |						 |
# |<---->|<-- fnameindent 8		 |
# |								 |
# |<---------------------------->|<-- paramindent 32
#
#
# Function pointer declaration:
# 0	   5	10	 15	  20   25	30	 35	  40   45	50	 55
# |	   |	|	 |	  |	   |	|	 |	  |	   |	|	 |
#		  _BioAPI_Function_PTR		Function;
# |		 |						 |
# |<---->|<-- funcptrindent 8	 |
# |								 |
# |<---------------------------->|<-- fptrnameindent 32
#
#
# Function definition:
# 0	   5	10	 15	  20   25	30	 35	  40   45	50	 55
# |	   |	|	 |	  |	   |	|	 |	  |	   |	|	 |
#		  BioAPI_RETURN BioAPI BioAPI_SomeFunc(
# |		 |						  uint32 Param1,
# |		 |						  uint32 Param2 )
# |		 |{						 |
# |		 |	  return BioAPI_OK;	 |
# |		 |}	 |					 |
# |		 |	 |					 |
# |		 |	 |					 |
# |<---->|<-- fnameindent 8		 |
# |			 |					 |
# |			 |					 |
# |<-------->|<-- fbodyindent 12 |
# |								 |
# |								 |
# |<---------------------------->|<-- paramindent 32
#
###########################################################################

# Basic command line to execute the pre-processor on this system
$PREPROC = "cl /E /nologo";

# Directory where temporary files will be created
$TempDir = ".";

# Number of spaces to use when indenting lines
SetOptions( "paramindent 24 funcptrindent 4 fptrnameindent 40 fbodyindent 12" );

$FuncPtrIndent = 4;

# Fetch the template name and make sure it has teh proper extension
$Template = shift( @ARGV );
if ( $Template !~ /\..tp$/ )
{
	Syntax();
	die "$Template is not a template file!\n";
}

# Fetch the pre-processor commands
@PreProcCmds = @ARGV;

# Create the output file name
$DestFile = $Template;
$DestFile =~ s/\.(.)tp$/\.$1/;

# Initialize the sequency hash.
%sequence = ();

print( "Pre-processor: $PREPROC @PreProcCmds\n" );
print( "Template File: $Template\n" );
print( "Destination File: $DestFile\n" );

ProcFile();

#
# END
#

# ProcFile
#
# Processes the file $Template and sends the result to $DestFile.
sub ProcFile()
{
	# Open the input and output files
	open SRC, "<$Template" || die "Could not open input file $Template\n";
	open DEST, ">$DestFile" || die "Could not open output file $DestFile\n";

	# Run through the file looking for #process_start directives
	while ( <SRC> )
	{
		if ( /^\#process_start\s/ )
		{
			SetOptions( $_ );
			PreProcessSection();
		}
		else
		{
			print DEST;
		}
	}
}

sub SetOptions
{
	my $Options = shift( @_ );
	local $i;

	if ( $Options =~ /paramindent\s?(\d+)/ )
	{
		$ParamIndent = int $1;
		$ParamIndentString = BlankString( $ParamIndent );
	}
	if ( $Options =~ /funcptrindent\s?(\d+)/ )
	{
		$FuncPtrIndent = int $1;
		$FuncPtrIndentString = BlankString( $FuncPtrIndent );
	}
	if ( $Options =~ /fptrnameindent\s?(\d+)/ )
	{
		$FuncPtrNameIndent = int $1;
	}
	if ( $Options =~ /fnameindent\s?(\d+)/ )
	{
		$FuncNameIndent = int $1;
		$FuncNameIndentString = BlankString( $FuncNameIndent );
	}
	if ( $Options =~ /fbodyindent\s?(\d+)/ )
	{
		$FuncBodyIndent = int $1;
		$FuncBodyIndentString = BlankString( $FuncBodyIndent );
	}
}

sub BlankString
{
	my $Length = shift( @_ );
	my @Occurences = ();

	# This works because setting $# will indicate the largest index value,
	# and since the default index starting value is 0, the number of elements
	# in @Occurences is actually $Length+1.	 Therefore, calling join will
	# produce the proper number of glue strings.

	$#Occurences = $Length;

	return join(" ", @Occurences);
}

sub PreProcessSection()
{
	my @SubjectLines, $line, $keepgoing;

	# Build the list of lines to pre-process
	$keepgoing = 1;
	while ( $keepgoing )
	{
		$line = <SRC>;
		if ( defined( $line ) && ( $line !~ /^\#process_end\s/ ) )
		{
			push( @SubjectLines, $line );
		}
		else
		{
			$keepgoing = 0;
		}
	}

	# Pre-process the block if it is not empty
	if ( $#SubjectLines > 0 )
	{
		# Write the lines to pre-process to a temp file
		open TEMP, ">$TempDir\/tmp$$" || die "Could not open temporary file!\n";
		print TEMP @SubjectLines;
		close TEMP;

		# Execute the pre-processor on the temp file
		open CPPSRC, "$PREPROC @PreProcCmds $TempDir\/tmp$$|" ||
			die "Could not run C pre-processor!\n";
		@CppOutput = <CPPSRC>;
		close CPPSRC;
		unlink( "$TempDir\/tmp$$" );

		# Post-process the pre-processor output
		PostProcess();
	}
}

sub PostProcess()
{
	local $line;
	local $funcname, $funcparams, $funcbody, $param, $index, $block_depth, $space;

	$block_depth = 0;

	# Trim the trailing newline off of each line
	chomp @CppOutput;

	# Process each line
	while ( defined( $line = shift( @CppOutput ) ) )
	{
		if ( ( $line =~ /^\#line\s/ ) || ( $line =~ /^\s*$/ ) )
		{
			next;
		}
		else
		{
			if ( $line =~ /^_BioAPI_.*/ )
			{
				# line with a function table declaration

				# Strip whitespace from the declaration
				$line =~ s/\s?(.*)?\s*$/$1/;

				# Split the line into it's components
				( $TypeName, $PtrName ) = split( " ", $line );
				$RequiredLength = $FuncPtrNameIndent - $FuncPtrIndent - length( $TypeName );
				if ( $RequiredLength <= 0 )
				{
					print DEST "$FuncPtrIndentString$TypeName$FuncPtrIndentString$PtrName\n";
				}
				else
				{
					$PadString = BlankString( $RequiredLength );
					print DEST "$FuncPtrIndentString$TypeName$PadString$PtrName\n";
				}
			}
			elsif ( $line =~ /^(.*)?\((.*)?\);\s*$/ )
			{
				# line with a function declaration

				# Store declaration componts and strip the whitespace
				$funcname = $1;
				$funcparams = $2;
				$funcname =~ s/^\s?(.*)\s$/$1/;
				$funcparams =~ s/\s?(.*)\s$/$1/;

				# Output the function declaration
				print DEST "$FuncNameIndentString$funcname\(\n";

				# Output the function parameters
				@Params = split( /\s?,\s?/, $funcparams );
				$funcparams = join( ",\n$ParamIndentString", @Params );
				print DEST "$ParamIndentString$funcparams \);\n\n";
			}
			elsif ( $line =~ /^(.*)?\((.*)?\)\s*{(.*)?}\s*$/ )
			{
				# line with a function definition

				# Store declaration componts and strip the whitespace
				$funcname = $1;
				$funcparams = $2;
				$funcbody = $3;
				$funcname =~ s/^\s?(.*)\s$/$1/;
				$funcparams =~ s/\s?(.*)\s$/$1/;

				# Output the function declaration
				print DEST "$FuncNameIndentString$funcname\(\n";

				# Output the function parameters
				@Params = split( /\s?,\s?/, $funcparams );
				$funcparams = join( ",\n$ParamIndentString", @Params );
				print DEST "$ParamIndentString$funcparams \)\n";

				# Output the function body
				print DEST "$FuncNameIndentString\{\n";

				$funcbody =~ s/^\s*/$FuncBodyIndentString/o;
				$funcbody =~ s/([;}])/$1\n$FuncBodyIndentString/go;
				$funcbody =~ s/\n[ \t\r\n]*/\n$FuncBodyIndentString/go;
				$funcbody =~ s/\s*$//o;

				$param = @Params ? $Params[0] : "";
				$param =~ s/\*/ /go;
				$param =~ /\s*(\w+)$/;
				$param = $1;

				$funcbody =~ s/FIRST_FUNC_PARAM/$param/g;

				# Event notify functions should return BioAPI_OK.
				#
				if ($funcname !~ /_EventNotify$/o)
				{
					$funcname =~ /(\w+)$/o;	 # Get the last token.
					$funcname = to_error_code($1);
					$funcbody =~ s/FUNC_NAME_AS_ERROR/$funcname/g;
				}
				else
				{
					$funcbody =~ s/FUNC_NAME_AS_ERROR/OK/go;
				}

				print DEST "$funcbody\n";
				print DEST "$FuncNameIndentString\}\n\n";
			}
			elsif ( $line =~ /^\s*PREPROCESSOR_ERROR_DEFINE\s*\((.+)\)\s*$/o )
			{
				# line with an error code definition

				# BioAPI_, name, BioAPI_AC_PRIVATE_ERROR [,SEQUENCE1]
				@Params = split(/,/, $1);
				foreach $param (@Params)
				{
					$param =~ s/\s*(.*)\s*/$1/o;
				}

				if (defined($sequence{$Params[3]}))
				{
					$sequence{$Params[3]}++;
				}
				else
				{
					$sequence{$Params[3]} = 1;
				}

				print DEST "$FuncNameIndentString#define $Params[0]",
							to_error_code($Params[1]),
							" ($Params[2] + $sequence{$Params[3]})\n";
			}
			else
			{
				$line =~ s/^(\s*)//o;
				$space = $1;

				for ($index = index($line, "}", $[ - 1);
					 $index != ($[ - 1);
					 $index = index($line, "}", $index + 1))
				{
					$block_depth--;
				}

				if (!$block_depth)
				{
					print DEST "$space$line\n";
				}
				else
				{
					print DEST BlankString($FuncBodyIndent * $block_depth), "$line\n";
				}

				for ($index = index($line, "{", $[ - 1);
					 $index != ($[ - 1);
					 $index = index($line, "{", $index + 1))
				{
					$block_depth++;
				}
			}
		}
	}
}

# Syntax
#
# Prints the usage syntax for the script
sub Syntax()
{
	print( "SYNTAX: template_proc template_file \[pre-processor arguments\]\n" );
	print( "\ttemplate_file must have a .?tp extension.\n" );
	print( "\tOnly -D, -I, and -L -pre-proc arguments should be used.\n\n" );
}

sub to_error_code
# to_error_code() - Converts a string to its equivalent form as an error code.
# PARAMETERS:
#	  $str - The string.
# RETURN:
#	  The string as an error code.
{
	my ($str) = $_[0];

	$str =~ s/BioAPI/BIOAPI/go; # So BioAPI doesn't become Bio_API
	$str =~ s/([a-z]+)/$1_/go;	# Add an underscore after every lowercase block.
	$str =~ s/_$//o;			# Remove any trailing underscores.

	return uc($str);			# Convert all of it to uppercase.
}
