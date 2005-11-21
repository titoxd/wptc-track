#!/usr/bin/env bash
#
# GGZ Gaming Zone bootstrap script for developers.
# To be used for SVN checkouts. Needs bash and perl installed.

srcdir=`dirname $0`

if test -z "$*"; then
  if test -z "$NOCONFIGURE"; then
    echo "** Warning: I am going to run 'configure' with no arguments."
    echo "** If you wish to pass any to it, please specify them on the"
    echo "** '$0' command line."
    echo
  fi
fi

echo -n "Bootstrapping GGZ... "
echo -n "[prerequisites]"

# Make sure autotools are installed

version_check()
{
log="$log\t++ Checking for $1,"
($1 --version >/dev/null 2>&1) || { log="$log not found!\n"; bailout=1; return; }
vline=`$1 --version | head -1`
needed="$2"

version=`echo $vline | perl -e "\\$_ = <STDIN>; \\$_ =~ m/(\d[\.\d]+)/; print \\$1"`
vmajor="0`echo $version | cut -d . -f 1`"
vminor="0`echo $version | cut -s -d . -f 2`"
vmicro="0`echo $version | cut -s -d . -f 3`"
nmajor="0`echo $needed | cut -d . -f 1`"
nminor="0`echo $needed | cut -s -d . -f 2`"
nmicro="0`echo $needed | cut -s -d . -f 3`"

old=0
if [ $vmajor -lt $nmajor ]; then old=1;
elif [ $vmajor -eq $nmajor ] && [ $vminor -lt $nminor ]; then old=1;
elif [ $vmajor -eq $nmajor ] && [ $vminor -eq $nminor ] && [ $vmicro -lt $nmicro ]; then old=1;
fi

vall="$vmajor.$vminor.$vmicro"
nall="$nmajor.$nminor.$nmicro"
vversion=`echo $vall | perl -e "\\$_ = <STDIN>; \\$_ =~ s/(^|\.)0(\d+)/\\$1\\$2/g; print"`
nversion=`echo $nall | perl -e "\\$_ = <STDIN>; \\$_ =~ s/(^|\.)0(\d+)/\\$1\\$2/g; print"`

log="$log need $nversion, found $vversion -"
if test $old = "1"; then
  log="$log too old!\n"
  bailout=1
else
  log="$log ok.\n"
fi
}

log=""
bailout=0
need_libtool=0

(grep "\bAC_PROG_LIBTOOL" $srcdir/configure.ac >/dev/null) && need_libtool=1
(grep "\bAC_GGZ_PLATFORM" $srcdir/configure.ac >/dev/null) && need_libtool=1

version_check "autoconf" "2.57"
version_check "automake" "1.7"
if test "x$need_libtool" = "x1"; then
	version_check "libtool" "1.4.4"
fi
version_check "gettext" "0.10.40"

if test "x$bailout" = "x1"; then
  echo
  echo "** Error: some prerequisites could not be found:"
  echo -e $log
  exit 1
fi

# Run autotools suite

if test -d $srcdir/m4; then
	echo -n "[m4]"
	cat $srcdir/m4/*.m4 > $srcdir/acinclude.m4
fi
if test "x$need_libtool" = "x1"; then
	echo -n "[libtoolize]"
	(cd $srcdir && libtoolize --force --copy >/dev/null) || { echo "libtoolize failed."; exit; }
fi
echo -n "[aclocal]"
(cd $srcdir && aclocal) || { echo "aclocal failed."; exit; }
echo -n "[autoheader]"
autoheader -I $srcdir || { echo "autoheader failed."; exit; }
echo -n "[automake]"
(set -o pipefail && cd $srcdir && automake --add-missing --gnu 2>&1 | (grep -v installing || true)) || { echo "automake failed."; exit; }
if test -f $srcdir/am_edit; then
	echo -n "[am_edit]"
	perl $srcdir/am_edit --foreign-libtool || { echo "am_edit failed."; exit; }
fi
echo -n "[autoconf]"
autoconf -I $srcdir $srcdir/configure.ac > $srcdir/configure && chmod +x $srcdir/configure || { echo "autoconf failed."; exit; }
echo ""

# Run configuration

if test -z "$NOCONFIGURE"; then
  echo Running $srcdir/configure $conf_flags "$@" ...
  $srcdir/configure $conf_flags "$@"
else
  echo Skipping configure process as requested.
fi

