//ȭ�������ȭ
//lestat for ������
//������һ������,���ǻᴴ���漣.fool

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
                return notify_fail("��Ҫ��˭ʩչ��һ�����ȭ��\n");

        if(!me->is_fighting())
                return notify_fail("���ȭֻ����ս����ʹ�ã�\n");
                
        if( time()-(int)me->query_temp("xiao_end") < 5 )
          return notify_fail("������̫�����ױ����ֿ��ƣ�\n");

        if((int)me->query("force") < 500 )
                return notify_fail("�������������\n");

        if((int)me->query("kee") < 300 )
                return notify_fail("�����Ѫ���㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("boxing", 1) < 50)
                return notify_fail("���ȭ��̫�ʹ����һ�л������ѣ�\n");

	me->delete("env/brief_message");

	message_vision("\n$Nһ������,�����һ�����ȭ��\n", me);

	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	me->receive_damage("kee", 50);
	me->add("force", -100);
	
        if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }
        if (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0))  
                       {
                       	str=target->name()+HIM"��"+me->name()+"��һ��"NOR+HIY"�����ȭ��"+HIM"�����ˣ�";
	                 message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	               }
        me->set_temp("xiao_end",time());
	me->start_busy(2);
	return 1;
}

