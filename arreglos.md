 ø Arreglo de los descriptores 
 - modificamos la declaración del .h pipex().
 - Cambio een la definición de pipex() en pipex.c
 - eliminamos la parte donde pipex abre los archivos.

 Ahora ya no se encarga de abrir archivos, solo trabaja con los file descriptors que le pasan.

 1. STDOUT VACÍO CUANDO ESPERAS SALIDA

 📋 grep + wc: ❌ stdout mismatch
Esperado out> '1'
Recibido out> ''

✅ Posible causa:
Tu execve() puede estar fallando, o tus dup2() no están bien colocados. Confirma que:

Estás haciendo dup2() antes de cerrar los pipes.

El execve() no está fallando en silencio. Si falla, imprime perror.

