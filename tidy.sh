for f in `ls *.cpp *.h`
do
$HOME/uncrustify/build/uncrustify -c defaults.cfg -f $f > tidy_temp
cp tidy_temp "$f"_backup
mv tidy_temp $f
done
