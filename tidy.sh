for f in `ls *.cpp *.h`
do
$HOME/uncrustify/build/uncrustify -c defaults.cfg -f $f > tidy_temp
mv tidy_temp $f
done
