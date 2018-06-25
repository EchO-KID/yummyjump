ffmpeg=~/Dev/bin/ffmpeg/ffmpeg
convert=/Users/lzubiaur/Dev/tools/ImageMagick-6.8.3/bin/convert

# $ffmpeg -ss 00:00:00.000 -i yesbuddy.mov -pix_fmt rgb24 -r 10 -s 320x240 -t 00:00:10.000 output.gif
# $ffmpeg -i $1 -pix_fmt rgb24 -r 10 -s 320x240 output.gif

rm frames/*.gif
rm frames/*.png

# $ffmpeg -i $1 -vf scale=500:-1 -r 10 -y frames/ffout%03d.png # test1

$ffmpeg -i $1 -an -r 10 -y -ss 00:00:02 -t 8 -s 506x253 frames/ffout%03d.png
# $ffmpeg -i $1 -an -r 10 -y -s 506x253 frames/ffout%03d.png
# for file in frames/*png; do echo converting $ file ...; $convert $file frames/`basename $file .png`.gif; done
echo Create gif animation file...
$convert -delay 5 -loop 0 frames/*.png output/output.gif
echo Optimize gif file...
$convert -dither none -matte -depth 8 -deconstruct -layers optimizePlus -colors 128 output/output.gif output/output_optimized.gif
$convert -delay 1x8 -ordered-dither o8x8,8 -coalesce -layers OptimizeTransparency +map frames/*.gif output/output_optimized2.gif
