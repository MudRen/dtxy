// by gslxz@mhsj 1/7/2001
// bh.c ���Ƶ��
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object *member;
	string bh;
	int i;

	if( !arg)	return notify_fail("��Ҫ˵ʲô��\n");
	bh=(string)me->query("banghui");
	if( !bh)	return notify_fail("��û�����ᣬ�޷�ʹ�ð��Ƶ����\n");
	member=users();
	for(i=0;i<sizeof(member);i++)	{
		if( !objectp(member[i]))	member[i]=0;
		else if( !living(member[i]))	member[i]=0;
		else if( (string)member[i]->query("banghui")!=bh)	member[i]=0;
	}
	member-=({ 0 });
// by gslxz@mhsj 1/7/2001
	message("banghui",HIG"��"+bh+"��"+me->query("name")+"("+me->query("id")+")��"+arg+"\n"NOR,
		member);
	return 1;
}
int help(object me)
{
        write(@HELP
ָ���ʽ : bh <����>

��ָ�����ڰ���Ա���ڲ�������

HELP
        );
        return 1;
}
