CFLAGS=-O3 -march=native -mtune=native
variants=baseline count bitcount decrement bin4 bin5 bin8 vector tree treeasm bmi2

bench:V: $variants
	for i in $prereq
	do
		./$i
	done

clean:V:
	rm -f $variants

%: %.c harness.c
	$CC $CFLAGS -o $target $prereq
