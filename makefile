.SUFFIXES:

ifeq ($(strip $(DEVKITSH4)),)
$(error "Please set DEVKITSH4 in your environment. export DEVKITSH4=<path to sdk>")
endif

include $(DEVKITSH4)/exword_rules

# アプリ情報
TARGET   := vramfill
APPID    := HELLO
APPTITLE := VRAM Filler
APPMOD   := out/$(TARGET).d01

# ソースファイル
CFILES := main.c
SFILES :=

# 出力ファイル
OBJECTS := $(patsubst %.c, out/%.o, $(CFILES)) $(patsubst %.s, out/%.o, $(SFILES))

# ビルドフラグ
CFLAGS  := -O2 -fno-builtin -I$(DEVKITPRO)/libdataplus/include
ASFLAGS := -m4-nofpu
LDFLAGS := -nostdlib -L$(DEVKITPRO)/libdataplus/lib -ldataplus -lgraphics -lsh4a

# デフォルトターゲット
all: $(APPMOD)

# d01生成
out/$(TARGET).d01: out/$(TARGET).elf

out/diction.htm:
	@mkdir -p out
	echo '<html><head><title>$(TARGET)</title><meta name="soft" content="OFF"></head><body></body></html>' > $@

out/infodp5.htm:
	@mkdir -p out
	echo -e 'dicapl="700"\nid="$(TARGET)"\nhistory="OFF"\nkjump="OFF"' > $@

out/infogt5.htm:
	@mkdir -p out
	echo -e 'more_srch="OFF"\nnarrow_srch="OFF"\norder_srch="OFF"\ncenter="OFF"\ntts_lang="of"\naddin="ON,$(TARGET).d01"\njp_lang="of"\npic_prev="OFF"\nlist_idec="OFF"' > $@

out/fileinfo.cji:
	@mkdir -p out
	touch $@


#switch;


# elf生成
out/$(TARGET).elf: $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

# コンパイルルール
out/%.o: %.c
	@mkdir -p out
	$(CC) $(CFLAGS) -c -o $@ $<

out/%.o: %.s
	@mkdir -p out
	$(AS) $(ASFLAGS) -o $@ $<

# クリーン
clean:
	rm -rf out
