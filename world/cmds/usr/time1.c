// time.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
//          write("������" + NATURE_D->game_time() + "��\n");
              write( ctime(time())+ "��\n");
	return 1;
}

int help(object me)
{
     write(@HELP
ָ���ʽ: time

���ָ������֪�����ڵ�ʱ����

HELP
    );
    return 1;
}
