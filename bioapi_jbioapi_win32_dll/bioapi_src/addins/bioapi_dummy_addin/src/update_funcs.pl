#-----------------------------------------------------------------------
# File: UPDATE_FUNCS.PL
#
# Copyright (c) 1995-2000 Intel Corporation. All rights reserved.
#-----------------------------------------------------------------------
#

# update_funcs - Read in function declarations and spit out the same minus
#				 the semicolon in the current directory.
#

use File::Basename;
use FileHandle;
use strict;
use vars qw($usage $arg $path $file $path $ext $in_fh $line $comment $index
			$out_fh $fix);

$usage = "Usage: $0 <file.h> [<file.h> ...]\n";

die $usage if (!@ARGV);

foreach $arg (@ARGV)
{
	($file, $path, $ext) = fileparse($arg, (".h", ".H"));

	die $usage if (!defined($ext) || $ext eq "");

	$in_fh = new FileHandle($arg);
	die "$arg: $!\n" if (!defined($in_fh));

	$out_fh = new FileHandle(">$file.c");
	die "$arg: $!\n" if (!defined($out_fh));

	$comment = 0;
	while (<$in_fh>)
	{
		$line = $_;

		# Go down $line from left to right.	 Simply print any commented
		# segments, and process any non-commented segments.
		#
		# This would be much more elegant as a recursive function, but I've
		# already got this working.	 :)
		#
		while ($line ne "")
		{
			if ($comment)
			{
				$index = index($line, "*/");
				if ($index != -1)
				{
					$comment = 0;
					print $out_fh substr($line, 0, $index + 2);
					$line = substr($line, $index + 2);
				}
				else
				{
					print $out_fh $line;
					$line = "";
				}
			}
			else
			{
				$index = index($line, "/*");
				if ($index != -1)
				{
					$comment = 1;
					$fix = substr($line, 0, $index);
					$line = substr($line, $index);

					$fix =~ s/;//go;

					print $out_fh $fix;
				}
				else
				{
					$line =~ s/;//go;
					print $out_fh $line;
					$line = "";
				}
			}
		}
	}

	$out_fh->close();
	$in_fh->close();

	print "updated $file.c\n";
}
