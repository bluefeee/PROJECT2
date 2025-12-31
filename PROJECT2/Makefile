# 根目录 Makefile（整合 quickstart 目录内容）
CC = arm-linux-gcc
LVGL_DIR_NAME = lvgl
LVGL_DIR = ${shell pwd}
# 根目录原有 CFLAGS + quickstart 目录的 CFLAGS（去重并保留关键选项）
CFLAGS = -O3 -g0 \
	-I$(LVGL_DIR)/ -I$(LVGL_DIR)/lv_chinese_ime/ -I$(LVGL_DIR)/lv_chinese_ime/src \
	-I$(LVGL_DIR)/quickstart/include -I$(LVGL_DIR)/quickstart/include/util -I$(LVGL_DIR)/quickstart/include/base \
	-Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wextra -Wno-unused-function \
	-Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized \
	-Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits \
	-Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default \
	-Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare \
	-Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wstack-usage=2048 -Wno-unused-value \
	-lrt -lm -fno-strict-aliasing -fno-omit-frame-pointer -pipe -fPIC -MD -MP -fno-common \
	-freg-struct-return -fno-inline -fno-exceptions -Wfloat-equal -Wformat=2 -rdynamic \
	-fstrength-reduce -fno-builtin -fsigned-char -ffunction-sections -fdata-sections \
	-Wcast-qual -Waggregate-return -Winline -Wcast-align -Wredundant-decls -Wstrict-prototypes \
	-Wnested-externs
# 链接选项：原有 LDFLAGS + quickstart 的库依赖
LDFLAGS ?= -lm \
	-Wl,-z,relro,-z,now,-z,noexecstack \
	-L$(LVGL_DIR)/quickstart/lib -lpaho-mqtt3as -lssl -lcrypto -lpthread
BIN = demo
BUILD_DIR = build

# 自动创建 build 目录
$(shell mkdir -p $(BUILD_DIR))

# 根目录原有主源码
MAINSRC = ./main.c

# 包含 LVGL 相关 mk 文件
include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

# 根目录原有源码集合
CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c  
CSRCS += $(LVGL_DIR)/lvgl/src/font/SiYuanHeiTi_Heavy.c  # 字体文件
CSRCS += $(shell find -L $(LVGL_DIR)/Squareline -name "*.c" -type f)
CSRCS += $(shell find -L $(LVGL_DIR)/lv_chinese_ime -name "*.c" -type f)

# 整合 quickstart 目录的源码（对应原 quickstart Makefile 的 OBJS 对应的 .c 文件）
CSRCS += $(LVGL_DIR)/quickstart/src/util/string_util.c
CSRCS += $(LVGL_DIR)/quickstart/src/mqtt_c_demo.c
CSRCS += $(LVGL_DIR)/quickstart/src/cJSON.c

OBJEXT ?= .o

# 所有 .o 文件输出到 build/ 目录（统一路径）
AOBJS = $(addprefix $(BUILD_DIR)/, $(ASRCS:.S=$(OBJEXT)))
COBJS = $(addprefix $(BUILD_DIR)/, $(CSRCS:.c=$(OBJEXT)))
MAINOBJ = $(addprefix $(BUILD_DIR)/, $(MAINSRC:.c=$(OBJEXT)))

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC)
OBJS = $(AOBJS) $(COBJS)

all: default

# 编译规则：自动创建 build 下的子目录，编译所有 .c 文件
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)  
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $< -> $(dir $@)"

# 链接规则：整合所有 .o 文件和库依赖
default: $(AOBJS) $(COBJS) $(MAINOBJ) 
	$(CC) -o $(BIN) $^ $(LDFLAGS)
	@echo "LINK -> $(BIN)"

# 清理规则：删除 build 目录、可执行文件及 quickstart 相关临时文件
clean: 
	rm -rf $(BUILD_DIR) $(BIN)
	rm -f $(LVGL_DIR)/quickstart/*.d $(LVGL_DIR)/quickstart/*.o 
	@echo "Clean done"
