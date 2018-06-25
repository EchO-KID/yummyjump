tp=/Users/lzubiaur/Dev/tools/TexturePacker.app/Contents/MacOS/TexturePacker
convert="/ImageMagick-6.8.3/bin/convert"

# --variant 0.5:-hd --variant 1:-retina --variant 0.25:-sd  \
# options: --shape-debug

rm -rf output
rm -rf tmp
mkdir output 
mkdir tmp

ratios=( 100 50 25 ) # scaling in percent
maxtexsize=( 2048 1024 512 ) # Max texture size
resources=( ipadhd hd sd ) # resource folder name
# for all subdirectories in the `sprites` folder
for folder in `find ../Assets/svg/sprites -type d -mindepth 1`; do 
    spritesheet=`basename $folder`
    $tp --format cocos2d --force-publish \
        --algorithm MaxRects --pack-mode Best --maxrects-heuristics Best \
        --padding 2 --shape-padding 2 --border-padding 2 --inner-padding 0 --trim-mode Trim --trim-threshold 1 \
        --enable-rotation --extrude 0 \
        --opt RGBA8888 --png-opt-level 2 \
        --max-width 2048 --max-height 2048 --size-constraints AnySize \
        --variant 1:retina --variant 0.5:hd --variant 0.25:sd \
        --force-identical-layout \
        --data "../Resources/{v}/${spritesheet}.plist" --sheet "../Resources/{v}/${spritesheet}.png" \
        $folder
done

