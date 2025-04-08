CC			=	cc -I$(INCLUDE) -Wall -Wextra -Werror #-g3 -fsanitize=address

NAME		=	pipex
INCLUDE		=	include
SRCDIR		=	src/
OBJDIR		=	objs/
SRCS		=	$(SRCDIR)pipex.c $(SRCDIR)utils_pipex.c
OBJS		=	$(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)

LIBFT		=	src/libft/
LIBFT_A		=	$(LIBFT)libft.a

AR			=	ar rcs
RM			=	rm -f

all:		$(NAME)

$(NAME):    $(OBJS)
$(NAME):    $(OBJS)
				@( \
					i=1; \
					while :; do \
						case $$i in \
							1) dots="." ;; \
							2) dots=".." ;; \
							3) dots="..." ;; \
							4) dots="...." ;; \
							5) dots="....." ;; \
							6) dots="......" ;; \
							7) dots="......." ; i=0 ;; \
						esac; \
						printf "\rCompiling libft %s" "$$dots"; \
						sleep 0.15; \
						i=$$(expr $$i + 1); \
					done & \
					ANIM_PID=$$!; \
					make -C $(LIBFT) -s; \
					kill $$ANIM_PID; \
					wait $$ANIM_PID 2>/dev/null; \
					printf "\n"; \
				)
				@echo "Creating objects 🔨🪛"
				@$(CC) $(OBJS) $(LIBFT_A) -o $(NAME)
				@echo "Cooking up the program 🍲🍳"
				@echo "✅ Done ✅"
				@$(RM) 

$(OBJDIR)%.o: $(SRCDIR)%.c
				@mkdir -p $(OBJDIR)
				@$(CC) -c $< -o $@

clean:
				@$(RM) $(OBJS)
				@rm -rf $(OBJDIR)
				@make -C $(LIBFT) clean -s
				@echo "Cleaning up... 🧹💨"

fclean:			clean
				@make -C $(LIBFT) fclean -s
				@$(RM) $(NAME)
				@$(RM) $(EXEC)
				@$(RM) $(PROG_BAR_FILE)

re:				fclean all

.PHONY:       	all lib clean fclean re bonus