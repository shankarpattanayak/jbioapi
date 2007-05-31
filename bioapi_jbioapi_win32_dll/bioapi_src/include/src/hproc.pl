#-----------------------------------------------------------------------
# File: HPROC.PL
#
# Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
#-----------------------------------------------------------------------
#

###########################################################################
#
# SYNTAX: hproc template_file [ pre-processor arguments ]
#  Only -Dname, -I, and -L arguments should be used.
#
# This script will process a header template (.ht) file and output a final
# human readable header that has been partially pre-processed. The
# resulting header file has the same name as the template, with a .h
# extension.
#
# A template file is a standard C header with two extra pre-processor
# directives: #process_start and #process_end. The #process_start
# directive indicates that the C pre-processor and pretty-printing routines
# should be run on the template file until the end-of-file or #process_end
# directive is found. The contents of the source located between the
# #process_start and #process_end directives must be independent of any
# other process blocks or any code located outside of the block.
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
#	paramindent	   Specifies the number of blanks to plaec before each
#				   parameter of a function prototype or typedef. Each
#				   parameter is placed on a separate line.
#	funcptrindent  When a line starts with a function pointer type name,
#				   the line will be indented this number of blanks. The
#				   pointer type names are assumed to start with the pattern
#				   "_CSSM_".
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
#		  CSSM_RETURN CSSMAPI CSSM_SomeFunc(
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
#		  _CSSM_Function_PTR	  Function;
# |		 |						 |
# |<---->|<-- funcptrindent 8	 |
# |								 |
# |<---------------------------->|<-- fptrnameindent 32
#
###########################################################################

# Basic command line to execute the pre-processor on this system
$PREPROC = "cl /E /nologo";

# Directory where temporary files will be created
$TempDir = ".";

# Number of spaces to use when indenting lines
SetOptions( "paramindent 24 funcptrindent 4 fptrnameindent 40" );

$FuncPtrIndent = 4;

# Fetch the template name and make sure it has teh proper extension
$Template = shift( @ARGV );
if ( $Template !~ /\.htp$/ )
{
	Syntax();
	die "$Template is not a template file!\n";
}

# Fetch the pre-processor commands
@PreProcCmds = @ARGV;

# Create the output file name
$DestFile = $Template;
$DestFile =~ s/\.htp$/\.h/;

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
}

sub BlankString
{
	my $Length = shift( @_ );
	my $TempString = "";
	my $i;

	for ( $i = 0; $i < $Length; $i++ )
	{
		$TempString = "$TempString ";
	}

	return $TempString;
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
	local $funcname, $funcparams, $endstuff;

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
			if ( $line =~ /^_CSSM_.*/ )
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
			else
			{
				print DEST "$line\n";
			}
			$LastLine = $line;
		}
	}
}


# Syntax
#
# Prints the usage syntax for the script
sub Syntax()
{
	print( "SYNTAX: hproc template_file \[pre-processor arguments\]\n" );
	print( "\ttemplate_file must have a .ht extension.\n" );
	print( "\tOnly -D, -I, and -L -pre-proc arguments should be used.\n\n" );
}

