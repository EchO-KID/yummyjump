find ../Classes -name "*.h" | while read line; do
sed '/#endif /i\
@XmlRootElement(name="ABC")

' file > outFile
done

exit 0
find ../Classes -name "*.cpp" | while read line; do
echo NS_PIX2D_END >> $line
done
