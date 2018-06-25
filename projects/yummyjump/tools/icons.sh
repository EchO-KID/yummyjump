convert="/ImageMagick-6.8.3/bin/convert"
folder=../Assets/svg/icons
ios=$folder/iOS
ios2x=$folder/iOS_2x
android=../proj.android/res
icon=$folder/icon.png

#ios
if [ "$1" == "ios" ]; then
$convert $icon -resize 29x29 $ios/app_icon_29.png
$convert $icon -resize 40x40 $ios/app_icon_40.png
$convert $icon -resize 50x50 $ios/app_icon_50.png
$convert $icon -resize 57x57 $ios/app_icon_57.png
$convert $icon -resize 60x60 $ios/app_icon_60.png
$convert $icon -resize 72x72 $ios/app_icon_72.png
$convert $icon -resize 76x76 $ios/app_icon_76.png

$convert $icon -resize 58x58 $ios2x/app_icon_29_x2.png
$convert $icon -resize 80x80 $ios2x/app_icon_40_x2.png
$convert $icon -resize 100x100 $ios2x/app_icon_50_x2.png
$convert $icon -resize 114x114 $ios2x/app_icon_57_x2.png
$convert $icon -resize 120x120 $ios2x/app_icon_60_x2.png
$convert $icon -resize 144x144 $ios2x/app_icon_72_x2.png
$convert $icon -resize 152x152 $ios2x/app_icon_76_x2.png
elif [ "$1" == "android" ]; then
#android 
$convert $icon -resize 32x32 $android/drawable-ldpi/icon.png
$convert $icon -resize 48x48 $android/drawable-mdpi/icon.png
$convert $icon -resize 72x72 $android/drawable-hdpi/icon.png
else 
    echo "Usage: icons ios|android"
fi
