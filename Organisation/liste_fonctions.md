### Utilisation des fonctions dans Minishell

## stat() & lstat() & fstat()

int stat(const char *restrict pathname, struct stat *restrict statbuf);
int lstat(const char *restrict pathname, struct stat *restrict statbuf);
int fstat(int fd, struct stat *statbuf);

Ces fonctions servent a récuperer les informations d'un fichier.
stat() répcupère l'état du pichier renseigné pointé par path et les écrits sur le tampon buff
lstat() est pareil sauf que si path est un lien symbolique il donne l'état du lien plutot que du fichier
fstat() est aussi pareil sauf qu'il pointe sur le descripteur de fichier

## opendir()

DIR *opendir(const char *name);

ouvre un flux répertoire conrespondant au répertoire name et renvoie un pointeur sur ce flux

## closedir()

int closedir(DIR *dirp);

ferme le flux et libere la memoire

## readdir()

struct dirent *readdir(DIR *dirp);

va lire l'entrée suivante des fichier contenu dans le flux rpertoire

## int isatty(int fd);

Booléen adin de vérifier si le descripteur de fichier ouvert est connecté à un terminal (= si 1 = interactive shell mode).

interactive mode = we are able to give it
input, and it will execute commands. non-interactive mode =
you cannot give it input, it executes commands from a script.

## ttyname()

si le descripteur de fichier est associé à un terminal, on renvoie le nom du terminal ou NULL
Exemple : 

    da=open("/dev/tty",O_RDWR);
    db=open("/dev/ttyp2",O_RDWR);
    a=ttyname(da);
    printf(" %s",a);
    b=ttyname(db);
    printf(" %s,b); 

## ttyslot()

int ttyslot(void);
renvoie la position de l'entrée du terminal en cours dans un fichier.


## ioctl()

int ioctl(int fd, unsigned long request, ...);
input-output control, est un appel systeme spécifique pour des opéraions entrée sortie spécifique à un périférique qui ne peuvent pas etre executée par un appel systeme classique. Elle modifie le comportement des périphérique caché dans des fichiers spéciaux comme le tty

Liste des requetes :
https://linux.die.net/man/2/ioctl_list

## getenv()

char *getenv(const char *name);
cete fonction cherche dans les variables d'enviornemnt name et return la string ou NULL si rien trouvé
idéale pour chercher le PATH pour la fonction execve ou avoir des informaion sur tnn terminal.

Exemple : 
    getenv("PATH");


## tcsetattr()

int tcsetattr(int fildes, int optional_actions, const struct *termios_p);

Elle applique les modifications qu'on a faite dans la structure termios.
Avec trois options d'actions :

TCSANOW : les modifications sont appliques maintenant
TCSADRAIN : les modifications sont appliques uniquement si les operations d'ecritures sur le fd sont terminees, a utiliser si les parametres des fd sont modifies
TCSAFLUSH : les modifications sont appliques uniquement si les operations d'ecritures sur le fd sont terminees, Les entrees qui n'ont pas ete traites seront supprimees avant tout autres modifications

## tcgetattr()

int tcgetattr(int fildes, struct termios *termios_p);

Cette fonction sert a copier les parametres du terminal (fd) dans une struct termios.

tcflag_t c_iflag;      /* modes d'entrée */
tcflag_t c_oflag;      /* modes de sortie */
tcflag_t c_cflag;      /* modes de contrôle */
tcflag_t c_lflag;      /* modes locaux */
cc_t     c_cc[NCCS];   /* caractères de contrôle */

Pour voir les differents flags : http://manpagesfr.free.fr/man/man3/termios.3.html

Exemple d'application de ces deux fonctions
https://ftp.lip6.fr/pub/atari/Linux68k/French/DaCri/PR1.0.1/docs/fr_howto/HOWTO/html/Serial-Programming-HOWTO.html#toc3


## Les fonctions tgetent(): 
term.h
curses.h 
Ces fonctions aide à la conversion d'informations pour les programmes qui utilisent la bibliothèque termcap.
Termcap "terminal capacity", est une bibliothèque et une base de donnees universelle permmetant d'affichier les resultats en mode texte sur les terminaux.

# tgetent()

int tgetent(char *bp, const char *name);
Elle va chercher les informations de ton terminal, afin que le programme les utilise et puisse communiquer avec lui. avec pour argument le buffer qui contiendra les infos du teminal et son nom.

Exemple : 
    int ret;
    char *term_type = getenv("TERM");
    ret = tgetent(NULL, term_type);

# int tgetflag(char *id);

Boolean afin de verifier les capacites du terminal. il prend en argument une string correspondant a un element du termcap.

Exemple :
    if (tgetflag("os") != 0)
    {
        /*Condition*/
    }

# int tgetnum(char *id);
Permet de recuperer des informations numeriques de notre terminal("colonne, lignes..."). il prend en argument une string correspondant a un element du termcap.

Exemple :
    int column_count = tgetnum("co");
    int line_count = tgetnum("li");

# char *tgetstr(char *id, char **area);
Permet de recuperer des commandes de la bibliothèque termcap sous forme de sequence d'echappement.

Une sequence d'echappement est une seaquence de quelques octects (des chars), qui permet d'appliquer une action specifique a un ternimal.

Exemple :
    char *cl_cap = tgetstr("cl", NULL);

# char *tgoto(const char *cap, int col, int row);

cette fonction va generer la commande termcap renseigne dans le terminal. Le premier arguement la commande termcap, les deux derniers la ligne et le colonne ou elle sera genere.

# int tputs(const char *str, int affcnt, int (*putc)(int));

cette fonction va executer la commande termcap recupere par la fonction tgetstr(). Le premier arguement la commande termcap, la deuxieme le nombre de lignes dans le terminal affecte, et la troisieme une fonction pour afficher le resultat.
    
Exemple :
    char *cl_cap = tgetstr("cl", NULL);
    tputs (cl_cap, 1, ft_putchar);

# getcwd(char *buf, size_t size)

The  getcwd()  function copies an absolute pathname of the current working directory to the array pointed  to by buf, which is of length size.

If  the length of the absolute pathname of the current working  directory,  including  the  terminating  null byte,  exceeds size bytes, NULL is returned, and errno is set to ERANGE; an application should check for this error, and allocate a larger buffer if necessary.