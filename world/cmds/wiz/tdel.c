// toptenadd.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string type,player;

	seteuid(geteuid(me));
	if (!arg||sscanf(arg,"%s %s",type,player)!=2)
		return notify_fail("ָ���ʽ : tdel <����> <���ID>\n");
	if (TOPTEN_D->topten_del(player,type)!=-1)
	 write("�Ѿ����ɾ����\n");
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : tdel <����> <���ID>
HELP
    );
    return 1;
}
