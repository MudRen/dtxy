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
                return notify_fail("��Ҫ��˭ʩչ��һ�������ף�\n");

        if(!me->is_fighting(target))
                return notify_fail("������ֻ����ս����ʹ�ã�\n");
                
	if(me->query("family/family_name")!="���ƶ�")
           return notify_fail("�������ס�ֻ�л��ƶ����˲ſ����ã�\n");

       if( time()-(int)me->query_temp("xiao_end") < 5 )
          return notify_fail("�����ö�Ͳ����ˣ�\n"); 
          
        if((int)me->query("force") < 500 )
                return notify_fail("�������������\n");

        if((int)me->query("kee") < 300 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("moyun-shou", 1) < 70)
                return notify_fail("���Ħ���ּ��𻹲�����ʹ����һ�л������ѣ�\n");

	me->delete("env/brief_message");

	message_vision("\n$N���һ���������ס���\n", me);


	me->set_temp("moyunshou_per", 6);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));

	me->delete_temp("moyunshou_per");

	me->receive_damage("kee", 50);
	me->add("force", -100);
    if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
                       {str=target->name()+HIM"��"+me->name()+"��Ħ�ƶ���ѧ"NOR+HIC"�������ס�"+HIM"ը���ˣ�";
	                 message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	               }
    me->set_temp("xiao_end",time());
	return 1;
}

