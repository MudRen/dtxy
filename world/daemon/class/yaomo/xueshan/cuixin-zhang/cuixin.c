#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
	string msg,str;        
	if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�д����ƣ�\n");

        if(!me->is_fighting(target))
                return notify_fail("������ֻ����ս����ʹ�ã�\n");
	
	if(me->query("family/family_name")!="��ѩɽ")
           return notify_fail("�������ơ�ֻ�д�ѩɽ���˲ſ����ã�\n");
        
        if( time()-(int)me->query_temp("xiao_end") < 5 )
          return notify_fail("�����ö�Ͳ����ˣ�\n");

        if((int)me->query("force") < 500 )
                return notify_fail("�������������\n");

        if((int)me->query("kee") < 300 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("cuixin-zhang", 1) < 100)
                return notify_fail("��Ĵ����Ƽ��𻹲�����ʹ����һ�л������ѣ�\n");

	me->delete("env/brief_message");

	message_vision("\n$N���һ���������ơ���\n", me);


	me->set_temp("cuixin_per", 5);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	me->delete_temp("cuixin_per");

	me->receive_damage("kee", 50);
	me->add("force", -100);
    if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
                       {str=target->name()+HIM"��"+me->name()+"�ô�ѩɽ��ѧ"NOR+HIR"�������ơ�"+HIM"�����ˣ���˵ʬ���������������÷��飡";
	                 message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	               }
    me->reset_action();
    me->set_temp("xiao_end",time());
	return 1;
}
