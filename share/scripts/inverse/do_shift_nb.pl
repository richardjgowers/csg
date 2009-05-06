#! /usr/bin/perl -w
#
# shifts the beginning of a non-bonded delta potential which is not in the update
# region to same as first value which is in region. It also shits the whole dpot 
# that it is zero at r_cut
#
# TODO: care about flags, not tested
#
use strict;

( my $progname = $0 ) =~ s#^.*/##;

# source the function file
(my $function_file=`$ENV{SOURCE_WRAPPER} functions perl`) || die "$progname: $ENV{SOURCE_WRAPPER} function perl failed\n";
chomp($function_file);
(do "$function_file") || die "$progname: source $function_file failed\n";
######

die "2 parameters are nessary, <infile> <outfile>\n" if ($#ARGV<1);

my $infile="$ARGV[0]";
my $outfile="$ARGV[1]";

print("$infile, $outfile\n");

my $r_cut=csg_get("max");

# read in the current dpot
my @r;
my @dpot;
my @flag;
(readin_table($infile,\@r,\@dpot,\@flag)) || die "$progname: error at readin_table\n";

# find index of cutoff
my $i_cut;
for($i_cut=0; ($i_cut<$#r-1) && ($r[$i_cut]<$r_cut); $i_cut++) {}
# find last u/o
my $i_first;
for($i_first=0; ($i_first<$#r) && ($flag[$i_first] =~ /[uo]/); $i_first++) {}

# shift beginning
for(my $i=0; $i<$i_first; $i++) {
    $dpot[$i] = $dpot[$i_first];
    $flag[$i]="o"
}

# bring end to zero
for(my $i=0; $i<$i_first; $i++) {
    $dpot[$i] -= $dpot[$i_cut];
}

# save to file
saveto_table($outfile,\@r,\@dpot,\@flag) || die "$progname: error at save table\n";