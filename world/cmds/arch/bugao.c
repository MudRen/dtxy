// bugao.c
#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
if(me->query("id")!="bear")
return notify_fail("��û��Ȩ��ʹ�á�\n");
if (!arg) return notify_fail("����Ҫ����ʲô?\n");
shout(me->name() + HIR"��"NOR""HIC"�� �� �� Ƶ ��"HIR"��"HIY":" +arg +"
\n"NOR);
write(HIC"��"NOR""HIC"�� �� �� Ƶ ��"HIC"��"HIW":" +arg +"\n"NOR);
   return 1;
}
int help(object me)
{
  write(@HELP
ָ���ʽ : bugao <ѶϢ>

���ָ�����㽫 <ѶϢ> ���ͳ�ȥ, ����������Ϸ�е��˶�
��������Ļ�.

see also : tune
HELP
    );
    return 1;
}
