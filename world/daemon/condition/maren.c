#include <ansi.h>
inherit F_CLEAN_UP;

string *msgs = ({
  "����¶��ɫ��������˼��˵������ʵ�Ҳ������˵ģ���",
  "��ͻȻ���û���������ô������ô�����",
  "�������Լ����������У����ɲ����ú���䤱���",
  "�����һ������˵��������������˵��³�!��",
});

int update_condition(object me, int duration)
{       
if(duration>1) 
{
me->apply_condition("maren", duration-1);  
   if(environment(me)->query("short")!=HIR"�������"NOR)
         {
                message_vision(HIR"ͻȻ������ð��ЩС���$N����Χס��\n"NOR,me);
                message_vision(HIW"$N��С���������ذ�������ˣ�\n"NOR,me);
                me->move("/d/city/prison");
         }
        else 
        {
            tell_object(me,HIR+msgs[random(sizeof(msgs))]+"\n"+NOR);
        }
}
else    {
              me->move("/d/city/kezhan");
	      me->save();
             message_vision(HIW"$N�����ͷţ�$N������شӰ���������˳�����\n"NOR,me);
             return 0;
        }
    return 1;
}
