#include "header.h"

int		 main(const int argc, const char** argv)
{
	tInfos	infos;

	if (registerArguments(&infos, argv + 1) == NULL)
		return (64);

	if (infos.help == true)
		help();
	else
		ping(&infos);

	(void) argc;

	return (0);
}

// icmp = internet control message protocol
// = protocole (suite TCP/IP) utilisé pour des messages de diagnositc/erreur
// > ne nécessite pas de port car la cible est l'hôte entier
// 2 types d'icmp > echo request et echo reply

// structure d'un paquet icmp :
// – en-tête IP (ajoutée par l'ordinateur à l'envoi)
// – en-tête icmp (type, code, checksum, identifiant et séquence)
// – données

// résolution DNS = traduction d'un nom de domaine (ex: localhost, google.com) vers une IP
// > vérification dans le cache DNS local, puis /etc/hosts, et enfin le résolveur DNS configuré

// checksum (= somme de contrôle) = valeur numérique calculée à partir des données d'un paquet
// = somme des blocs de 16 bits du paquet à envoyer
// > utilisé pour vérifier l'intégrité des données reçues/envoyées

// TTL = time to live
// = valeur décrémentée à chaque passage du paquet icmp par un routeur

// stddev = écart-type
// = dispersion autour de la moyenne
