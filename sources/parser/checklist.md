# 🔨 Le Parser : Créer les Structures de Commandes

Le parser est la deuxième étape. Il transforme la liste linéaire de tokens en une liste structurée de commandes exécutables.


## Les Responsabilités du Parser

Le parser a quatre missions clés. Il crée les structures de commandes avec leurs arguments. Il gère tous les types de séparateurs : pipes, opérateurs and et or. Il associe correctement les redirections aux commandes. Et pour les bonus, il gère la création des subshell avec parenthèses.

## L’Algorithme de Parsing
L’algorithme parcourt la liste de tokens et traite chaque type différemment.

Quand il rencontre un séparateur (pipe, and, or), il définit le séparateur de la commande courante, puis crée une nouvelle commande et l’ajoute à la liste.

Quand il rencontre une redirection, il l’ajoute à la commande courante, puis saute le token suivant qui contient le nom du fichier ou le mots de fin du heredoc.

Quand il rencontre une parenthèse ouvrante, il crée une commande spéciale de type subshell.

Quand il rencontre un mot normal, il l’ajoute simplement comme argument à la commande courante.

## Stocker le Séparateur dans Chaque Commande

Chaque commande stocke le séparateur qui la suit. C’est absolument crucial pour l’exécution correcte.

Prenons l’exemple echo a | cat && ls || pwd.

Après parsing, nous obtenons quatre commandes :

    Commande 1 : args [“echo”, “a”], separator pipe
    Commande 2 : args [“cat”], separator and
    Commande 3 : args [“ls”], separator or
    Commande 4 : args [“pwd”], separator none

Cette information de séparateur guidera toute la logique d’exécution.
