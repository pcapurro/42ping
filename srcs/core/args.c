#include "header.h"

void	*registerOptionsPOSIX(tInfos* infos, const char** argv)
{
	for (int i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '\0' || argv[i][0] != '-' || argv[i][1] != '-')
			continue ;

		if (strcmp("--verbose", argv[i]) == 0)
			infos->verbose = true;
		else if (strcmp("--numeric", argv[i]) == 0)
			infos->numeric = true;
		else if (strcmp("--ignore-routing", argv[i]) == 0)
			infos->routing = true;
		else if (strcmp("--flood", argv[i]) == 0)
			infos->flood = true;
		else if (strcmp("--help", argv[i]) == 0)
		{
			infos->help = true;
			return (infos);
		}
		else
		{
			error(2, argv[i], '\0');
			return (NULL);
		}
	}

	return (infos);
}

void	*registerOptionsGNU(tInfos* infos, const char** argv)
{
	if (infos->help == true)
		return (infos);

	for (int i = 0; argv[i] != NULL; i++)
	{
		if (argv[i][0] == '\0' || argv[i][0] != '-' || argv[i][1] == '-')
			continue ;

		for (int k = 1; argv[i][k] != '\0'; k++)
		{
			if (argv[i][k] == 'v')
				infos->verbose = true;
			else if (argv[i][k] == 'n')
				infos->numeric = true;
			else if (argv[i][k] == 'r')
				infos->routing = true;
			else if (argv[i][k] == 'f')
				infos->flood = true;
			else if (argv[i][k] == '?')
			{
				infos->help = true;
				return (infos);
			}
			else
			{
				error(3, NULL, argv[i][k]);
				return (NULL);
			}
		}
	}

	return (infos);
}

void	*registerHost(tInfos* infos, const char** argv)
{
	if (infos->help == true)
		return (infos);

	for (int i = 0; argv[i] != NULL && infos->host == NULL; i++)
	{
		if (argv[i][0] != '\0' && argv[i][0] != '-')
			infos->host = argv[i];
	}

	if (infos->host == NULL)
	{
		error(1, NULL, '\0');
		return (NULL);
	}

	return (infos);
}

void	*registerArguments(tInfos* infos, const char** argv)
{
	infos->verbose = false;
	infos->numeric = false;

	infos->routing = false;
	infos->flood = false;

	infos->help = false;

	infos->host = NULL;
	infos->ip = NULL;

	if (registerOptionsPOSIX(infos, argv) == NULL)
		return (NULL);

	if (registerOptionsGNU(infos, argv) == NULL)
		return (NULL);

	if (registerHost(infos, argv) == NULL)
		return (NULL);

	return (infos);
}
