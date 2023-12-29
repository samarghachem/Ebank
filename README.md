# E-Bank 

E-Bank est une application de gestion bancaire en langage C qui permet de gérer des comptes bancaires et leurs transactions.

## Fonctionnalités

- Création et gestion de comptes bancaires
- Mise à jour des informations du compte
- Réalisation de transactions comme les versements et retraits
- Gestion des virements entre comptes
- Affichage des transactions et détails des comptes
- Suppression de comptes
- Conversion de devises avec taux de change

## Détails d'Implémentation

L'application E-Bank est écrite en C et utilise les structures de données suivantes :

- **Liste Chaînée** : Pour stocker et gérer les comptes et les transactions.
- **Structures** : `compte` pour stocker les informations du compte, et `transaction` pour les détails des transactions.
- **Conversion de Devises** : Utilise des taux de change prédéfinis pour la conversion entre différentes devises.

## Installation

Pour exécuter l'application :

```bash
gcc -o ebank main.c
./ebank



