### Utilisation des fonctions dans Minishell

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

char *tgetstr(char *id, char **area);
Permet de recuperer des commandes de la bibliothèque termcap sous forme de sequence d'echappement.

Une sequence d'echappement est une seaquence de quelques octects (des chars), qui permet d'appliquer une action specifique a un ternimal.

Exemple :
    char *cl_cap = tgetstr("cl", NULL);

char *tgoto(const char *cap, int col, int row);

cette fonction va generer la commande termcap renseigne dans le terminal. Le premier arguement la commande termcap, les deux derniers la ligne et le colonne ou elle sera genere.

int tputs(const char *str, int affcnt, int (*putc)(int));

cette fonction va executer la commande termcap recupere par la fonction tgetstr(). Le premier arguement la commande termcap, la deuxieme le nombre de lignes dans le terminal affecte, et la troisieme une fonction pour afficher le resultat.
    
Exemple :
    char *cl_cap = tgetstr("cl", NULL);
    tputs (cl_cap, 1, ft_putchar);