#!/bin/bash

# سكريبت بناء ملف PKG لـ 3bodli Tools
TOOLCHAIN_DIR="$HOME/OpenOrbis-PS4-Toolchain"
BUILD_DIR="build"
TARGET="3bodli_tools"
TITLE_ID="BD3B00001"

echo "Building PKG for 3bodli Tools..."

# إنشاء مجلد للـ PKG
mkdir -p pkg/eboot
mkdir -p pkg/sce_sys
mkdir -p pkg/sce_sys/about

# نسخ الملفات
cp "$BUILD_DIR/$TARGET.elf" "pkg/eboot/boot.elf"
cp "assets/icon.png" "pkg/sce_sys/icon0.png"

# إنشاء param.sfo
"$TOOLCHAIN_DIR/bin/PkgTool.Core" \
    --content-id "IV0000-${TITLE_ID}_00-3BODLITOOLS0001" \
    --title-id "$TITLE_ID" \
    --title "3bodli Tools" \
    --app-type 1 \
    --app-ver "01.00" \
    --sdk-ver "05.050.000" \
    pkg/

# بناء الـ PKG
"$TOOLCHAIN_DIR/bin/PkgTool.Core" pkg/ "${TARGET}.pkg"

echo "PKG Created: ${TARGET}.pkg"
echo "Copy to USB and install on your PS4!"
