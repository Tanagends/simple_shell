#include "zimbo.h"
/** handle_colon - function to handle command separator
 *  @input: commands to seperate using the semi colony
 *  Return: Return nothing
*/
int handle_colon(char *input)
{
	char *colon_tok;
	int i;

	if (input == NULL)
	{
		return (-1);
	}
	colon_tok = _strtok(input, ";");
	
	while (colon_tok != NULL)
	{
		i = zimbo_execute(colon_tok);
	if (i != 0)
	{
		return (i);
	}
		colon_tok = _strtok(NULL, ";");
	}
		return (0);
}
