// eyeill.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
   if( duration < 1 ) return 0;
/*
   if( !living(me) ) {
      message("vision", me->name() + "的运气好，巫师还没有想好眼疾的效果。\n", environment(me), me);
   }
   else {
      tell_object(me, HIB "你的运气好，巫师还没有想好眼疾。\n" NOR );
      message("vision", me->name() + "的运气好，巫师还没有想好眼疾的效果。\n",
            environment(me), me);
   }
*/
//   me->receive_wound("kee", 1);
//   me->receive_damage("kee", 1);
   me->apply_condition("eyeill", duration - 1);

   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}

