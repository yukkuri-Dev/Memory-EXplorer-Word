.SUFFIXES:

ifeq ($(strip $(DEVKITSH4)),)
$(error "Please set DEVKITSH4 in your environment. export DEVKITSH4=<path to sdk>")
endif

include $(DEVKITSH4)/exword_rules

# アプリ情報
TARGET   := mdump
# AppIDは五文字でかいて
APPID    := MDUMP
APPTITLE := MemoryDumper4DP
APPMOD   := out/$(TARGET).d01

# ソースファイル
CFILES := main.c
SFILES :=

# 出力ファイル
OBJECTS := $(patsubst %.c, out/%.o, $(CFILES)) $(patsubst %.s, out/%.o, $(SFILES))

# ビルドフラグ
CFLAGS  := -O2 -fno-builtin -I$(DEVKITPRO)/libdataplus/include
ASFLAGS := -m4-nofpu
LDFLAGS := -nostdlib -L$(DEVKITPRO)/libdataplus/lib -ldataplus -lgraphics -lsh4a link.ld

# デフォルトターゲット
all: $(APPMOD) out/diction.htm out/infodp5.htm out/infogt5.htm out/fileinfo.cji


# d01生成
out/$(TARGET).d01: out/$(TARGET).elf

out/diction.htm:
	@mkdir -p out
	echo '<html><head><title>$(TARGET)</title><meta name="soft" content="OFF"></head><body></body></html>' > $@

out/infodp5.htm:
	@mkdir -p out
	printf 'dicapl="700"\nid="$(TARGET)"\nhistory="OFF"\nkjump="OFF"\n\n#switch;' > $@

out/infogt5.htm:
	@mkdir -p out
	printf 'more_srch="OFF"\nnarrow_srch="OFF"\norder_srch="OFF"\ncenter="OFF"\ntts_lang="of"\naddin="ON,$(TARGET).d01"\njp_lang="of"\npic_prev="OFF"\nlist_idec="OFF"' > $@

out/fileinfo.cji:
	@mkdir -p out
	touch $@


#switch;
out/baybay-o-and-elf:
	rm -f out/$(TARGET).elf
	rm -f out/*.o


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
