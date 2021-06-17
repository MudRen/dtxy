// ill_shanghan.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( duration < 1 ) return 0;
   if( !living(me) ) {
      message("vision", me->name() + "�䲻�����˸���ս��ͷ������ģ������ǵ��˺����ˡ�\n", environment(me), me);
   }
   else {
      tell_object(me, HIB "���˸���ս��ͷ������ģ������ǵ��˺����ˣ�\n" NOR );
      message("vision", me->name() + "�䲻�����˸���ս��ͷ������ģ������ǵ��˺����ˡ�\n",
          environment(me), me);
   }
   me->set_temp("death_msg","�����˺������ڻ�˯���������ǡ�\n");
   me->receive_wound("kee", 1);
   me->receive_damage("kee", 1);
   me->apply_condition("ill_shanghan", duration - 1);

   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}
