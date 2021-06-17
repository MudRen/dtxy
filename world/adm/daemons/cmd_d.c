//
// cmd_d.c
//
// By Annihilator (11/07/94)
// optimized by emotion (09/01/2006)

mapping search = ([]);

void rehash(string dir)
{
	int i;
	string *cmds;
	mapping hash_cmds;

	hash_cmds = ([]);

	if( dir[sizeof(dir)-1]!='/' ) dir += "/";
	cmds = get_dir(dir);
	i = sizeof(cmds);
	while(i--)
		if( sscanf(cmds[i], "%s.c", cmds[i]) )
			hash_cmds[cmds[i]] = 1;
	if (sizeof(hash_cmds)) 
		search[dir] = hash_cmds;
}

string find_command(string verb, string *path)
{
	int i;
	string cmd_path;
	mapping cmds;

	if( !pointerp(path) ) return 0;

	i = sizeof(path);
	while(i--) {
		cmd_path = path[i];
		if( undefinedp(search[cmd_path]) ) rehash(cmd_path);
		cmds = search[cmd_path];
		if( undefinedp(cmds) ) continue;
		if( cmds[verb] )
			return cmd_path + verb;
	}
	return 0;
}
