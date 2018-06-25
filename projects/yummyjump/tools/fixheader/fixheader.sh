echo "Please take a backup of your source files now!"
echo "Press ENTER to continue"
read 
find ../Classes -name "*.cpp" -o -name "*.h" | while read line; do
   echo "processing $line"
   ./rh/replace_header.sh $line
done

find ../Classes -name "*.h" | while read line; do
   ./include-guard-fixer.py --project PIX2D $line
done
