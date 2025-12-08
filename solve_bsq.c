# BSQ ALGORITHM - LINE BY LINE GUIDE

## 🎯 FORMULE À RETENIR

**dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1])**

---

## 📚 LES 3 CAS

1. **Obstacle** → dp[i][j] = 0
2. **Bord (i==0 ou j==0)** → dp[i][j] = 1  
3. **Milieu** → dp[i][j] = 1 + min(3 voisins)

---

## 📝 CODE LIGNE PAR LIGNE

**Line 1:** `int solve_bsq(t_bsq *bsq)`
→ Fonction qui prend la structure BSQ, return 0 si OK, 1 si erreur

**Line 3:** `int **dp = malloc(sizeof(int *) * bsq->height);`
→ Alloue un tableau 2D pour stocker les tailles de carrés
→ dp[i][j] = taille du plus grand carré qui se termine à (i,j)

**Line 4:** `int max_size = 0, max_i = 0, max_j = 0;`
→ Variables pour tracker le plus grand carré trouvé
→ max_size = la taille, (max_i, max_j) = coin bas-droit

**Line 5:** `int i = 0, j;`
→ Variables de boucle pour parcourir le tableau

**Line 7-8:** `if (!dp) return (1);`
→ Check si malloc a marché, sinon return erreur

**Line 10:** `while (i < bsq->height)`
→ Boucle sur chaque ligne

**Line 12:** `dp[i] = malloc(sizeof(int) * bsq->width);`
→ Alloue la mémoire pour cette ligne

**Line 13-14:** `if (!dp[i]) return (free_map((char **)dp, i), 1);`
→ Check malloc, si fail → free tout ce qui était alloué avant et return erreur

**Line 16:** `j = 0;`
→ Reset la colonne au début de chaque ligne

**Line 17:** `while (j < bsq->width)`
→ Boucle sur chaque colonne

**Line 19-20:** `if (bsq->map[i][j] == bsq->obstacle) dp[i][j] = 0;`
→ **CAS 1:** Si obstacle → taille = 0

**Line 21-22:** `else if (i == 0 || j == 0) dp[i][j] = 1;`
→ **CAS 2:** Si première ligne ou colonne → taille = 1

**Line 23-24:** `else dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]);`
→ **CAS 3:** LA FORMULE DP!
→ Prend le min des 3 voisins (haut-gauche, haut, gauche) et ajoute 1
→ Pourquoi? Si les 3 voisins peuvent supporter un carré de taille N, alors cette case peut supporter N+1

**Line 26-27:** `if (dp[i][j] > max_size) (max_size = dp[i][j], max_i = i, max_j = j);`
→ Si on a trouvé un plus grand carré, on update max_size et sa position

**Line 28:** `j++;`
→ Passe à la colonne suivante

**Line 30:** `i++;`
→ Passe à la ligne suivante

**Line 34:** `i = max_i - max_size + 1;`
→ Calcule la ligne de départ du carré
→ Formule: ligne_fin - taille + 1
→ Exemple: carré de taille 3 qui finit à ligne 5 → démarre à 5-3+1 = 3

**Line 35:** `while (i <= max_i)`
→ Boucle sur chaque ligne du carré à remplir

**Line 37:** `j = max_j - max_size + 1;`
→ Calcule la colonne de départ du carré (même formule)

**Line 38:** `while (j <= max_j)`
→ Boucle sur chaque colonne du carré à remplir

**Line 39:** `bsq->map[i][j++] = bsq->full;`
→ Remplace la case par le caractère "full" et incrémente j

**Line 40:** `i++;`
→ Passe à la ligne suivante du carré

**Line 43:** `free_map((char **)dp, bsq->height);`
→ Libère toute la mémoire du tableau DP

**Line 44:** `return (0);`
→ Return 0 = succès!

---

## 🧠 COMMENT ÇA MARCHE

**dp[i][j]** stocke la taille du plus grand carré dont le coin bas-droit est à (i,j)

**Pourquoi min(3 voisins)?**
- Si haut-gauche peut supporter taille N
- ET haut peut supporter taille N  
- ET gauche peut supporter taille N
- ALORS la case actuelle peut supporter taille N+1

---

## 📊 EXEMPLE VISUEL

**Input:**
```
. . . .
. . . .
. . x .
```

**DP table:**
```
1 1 1 1
1 2 2 2  ← max_size = 2 à position (1,3)
1 2 0 1
```

**Calcul du coin haut-gauche:**
- Ligne: 1 - 2 + 1 = 0
- Colonne: 3 - 2 + 1 = 2

**Result (remplir de (0,2) à (1,3)):**
```
. . o o
. . o o
. . x .
```

---

## ✅ CHECKLIST À RETENIR

1. ✅ Malloc le tableau DP (check les erreurs!)
2. ✅ Pour chaque case: 3 cas (obstacle/bord/milieu)
3. ✅ Tracker le max pendant qu'on construit le DP
4. ✅ Calculer top-left avec: `pos - size + 1`
5. ✅ Fill le carré dans la map originale
6. ✅ Free le DP et return 0

---

## 🔥 LA SEULE LIGNE VRAIMENT IMPORTANTE
```c
dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]);
```

C'est tout. Le reste c'est juste des checks et du remplissage.