#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11

# add to silence 'deprecated' warnings (bvercaem)
CFLAGS+= -Wno-deprecated-declarations

YELLOW			=	\x1b[33m
NO_COLOR		=	\x1b[0m
all: $(NOM)

$(NOM):	$(OBJ)
	@echo "$(YELLOW)Mlx ready$(NO_COLOR)"
	@ar -rc $(NOM) $(OBJ)
	@ranlib $(NOM)

clean:
	@rm -f $(NOM) $(OBJ) *~
	@rm -f mlx_app

re: clean all

MAKEFLAGS += --silent