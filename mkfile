CC=cc
CFLAGS=-O3

variants=baseline count bitcount decrement bin4 bin5 bin8 vector shuffle tree treeasm bmi2

bench:V: $variants
	for i in $prereq
	do
		./$i
	done

clean:V:
	rm -f $variants

%: %.c harness.c
	$CC $CFLAGS -o $target $prereq
