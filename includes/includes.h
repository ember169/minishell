/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 16:36:52 by lgervet           #+#    #+#             */
/*   Updated: 2026/07/06 00:01:12 by v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

# include "../libs/libft/includes/libft.h"
# include "core/structures.h"
# include "core/defines.h"
# include "modules/debug.h"
# include "modules/env.h"
# include "modules/lexer.h"
# include "modules/expander.h"
# include "modules/utils.h"
# include "modules/parser.h"
# include "modules/executor.h"
# include "modules/exit.h"
# include "modules/builtins.h"
# include "modules/signals.h"

#endif
