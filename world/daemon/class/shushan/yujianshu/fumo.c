//Modified by vikee for xlqy-zq station
//2000-12-5 10:19

#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
	int mypot,tapot,damage_pot,damage;
        weapon = me->query_temp("weapon");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ����˭��\n");
                if(me->query("family/family_name") != "��ɽ��" )
                return notify_fail("�����Ķ�͵ѧ�����书��\n");

        if(!me->is_fighting(target))
                return notify_fail("����û���ڴ�ܣ�\n");

        if((int)me->query("max_force") < 200 )
                return notify_fail("����ڹ�̫�\n");

        if((int)me->query("force") < 100 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") < 100 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
                
	if((int)me->query_skill("taoism", 1) < 50)
		return notify_fail("�����ʦ�����ȼ�����������ʹ����һ�У�\n");
	if( time()-(int)me->query_temp("fumo_end") < 5 )
                return notify_fail("�����ö��ˣ��Ͳ����ˣ�\n");
        me->set_temp("fumo_end",time());	

	me->delete("env/brief_message");
	target->delete("env/brief_message");
	message_vision(HIW"\n$N����Ĭ�������ھ�������"+weapon->name()+NOR+HIW"ϼ�����䣬�ڿշ���ֱն$n��\n\n"NOR,me,target);

	//�жϳɹ�ʧ������Ӧ�ô�����ԡ�
	//����Ƭ�δ�����һҶ֪��(vikee)�޸�
	mypot = (int)me->query_skill("sword");
        tapot=((int)target->query_skill("dodge")+(int)target->query_skill("parry"))/2;
        
        damage=(int)me->query_skill("yujianshu",1);           
	if (damage > 400) damage = 400;
        damage += me->query("force_factor");
	if ( random(mypot) > random(tapot)/2 )	//main condition vikee 2000-12-5 10:11
	{
	  	target->receive_damage("kee",damage,me);
		target->receive_wound("kee",damage/2,me);
	  	me->receive_damage("sen", 100);
          	me->add("force", -100);
          	me->start_busy(1); //busy time is added.    
          	COMBAT_D->report_status(target);
	}
	else
	{
	 	me->add("force", -100);
	 	message_vision(HIW"\n$n�����˼��ºò����׶㿪���⼸�����⣡\n\n"NOR,me,target);
 	}
        return 1;
}

   
