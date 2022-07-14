# minishell

Feature request for Patchking:

Возвращаемые значения для $? по образцу

// wait(&status);

// if (WIFSIGNALED(status))

//// return(WTERMSIG(status) + 128);

// if ("command not found")

//// 	            return (127);

// if ("command is not executable")

////           	  return (126);
  
  Для очистки памяти воспользуйся: command_memfree(t_cmd*) и memfree(t_list*)
  для обработки Heredoc - функцией heredoc.

На даный момент парсер готов на 99% (память освобождается из мэйна);
Обработка сигналов завершена на 50% (только сигналы получаемые основным процессом);
Build-in готовы на 80% (все кроме CD, который тоже должен работать, но почему-то не работает);

