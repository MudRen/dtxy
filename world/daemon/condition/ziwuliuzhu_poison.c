#include <ansi.h>
//#include <condition.h>

//inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        me->receive_wound("kee",50);
        me->receive_wound("sen",50);
        me->apply_condition("ziwuliuzhu_poison", duration - 1);
        tell_object(me, HIB "��о������ƺ�����Щʲô�����ƺ�����Щʲô�����˸����¡�\n" NOR );
        message("vision", me->name() + "�����㱣�����������ע�����ڷ��������ˡ�\n",environment(me), me);

        if( duration < 1 ) return 0;
        return 1;
}

