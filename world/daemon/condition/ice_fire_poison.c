//ice_fire_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( duration < 1 ) return 0;
   if( !living(me) ) {
      message("vision", me->name() + "�������࣬����Ѫ�죬ʹ��غ���һ����\n", environment(me), me);
   }
   else {   
      switch (random(2))
        {
         case 0:
              {
         tell_object(me, HIB "��Ȼһ���溮�ӵ�������������֫�ٺ������е��������������ˣ�\n" NOR );
         message("vision", me->name() + "������ÿ��Եγ�ˮ�������ظ�������������\n",environment(me), me);
               break;
               }
         case 1:
              {
         tell_object(me, HIR "��Ȼһ������ҵ��ӵ���ð����ҧ����澭���������е�����𶾷����ˣ�\n" NOR );
      message("vision", me->name() + "����Ѫһ���ĺ죬ʹ��ץ���Լ��Ĳ��ӡ�\n",environment(me), me);
               break;
              } 
         }
         }
       me->receive_wound("kee",20 + random(10));
        me->receive_wound("sen", 20 + random(10));
      me->apply_condition("ice_fire_poison", duration - 1);
   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}


