// xuanbu by Canoe
#include <ansi.h>;
int main(object me, string arg)
{
   if( !wizardp(me) )
     return notify_fail("Ŀǰ�ݲ�������� xuanbu��\n");
   if (!arg) return notify_fail("����Ҫ����ʲô?\n");
   shout( BLINK HIW"����ʦ���桿��" +NOR HIY+ arg + "\n"NOR);
    write("��������" + BLINK HIW"����ʦ���桿��" +NOR HIY+ arg + "\n"NOR);
   return 1;
}
int help(object me)
{
  write(@HELP
ָ���ʽ : xuanbu <ѶϢ>
 
���ָ�����㽫 <ѶϢ> ���ͳ�ȥ, ����������Ϸ�е��˶�
��������Ļ�����shoutΨһ��ͬ�ľ���player��֪������˭��
 
see also : tune
HELP
    );
    return 1;
}
 

