//Cracked by Roath
//Jiz
#include <ansi.h>

inherit SSERVER;

int perform(object me, object target)
{
	object *inv, obj;
	int i, mypot,tapot,temp_dodge,temp_spells;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С���Ԫһ�ơ���\n");
        if( !wizardp(me) && me->query("family/family_name")!="��������" )
                return notify_fail("���������Ӳ����á���Ԫһ�ơ���\n");
        if(!me->is_fighting(target))
                return notify_fail("����Ԫһ�ơ�ֻ����ս����ʹ�ã�\n");

	if( time()-(int)me->query_temp("xingyun_end") < 10 )
	return notify_fail("�����ö�Ͳ����ˣ�\n");
        if((int)me->query("max_force") < 200 )
                return notify_fail("�������������\n");

	if((int)me->query("force") < 200 )
		return notify_fail("����������㣡\n");

        if((int)me->query("sen") < 200 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

        if((int)me->query_skill("huntian-hammer", 1) < 30)
                return notify_fail("��Ļ��촸���𻹲�����ʹ����һ�л������ѣ�\n");

	message_vision(HIC"\n$N���㾫�񣬴��һ��������$n������ȫ��һ����\n"NOR, me, target);

	mypot = me->query_skill("hammer");
	//mypot=mypot*mypot*mypot/10 + (int)me->query("combat_exp");

	tapot = target->query_skill("parry",1)/2;
	tapot = tapot + target->query_skill("dodge",1)/3;
	//tapot=tapot*tapot*tapot/10 + (int)target->query("combat_exp");

//	write("mypot " + mypot + ", tapot " +tapot+ "\n");

	if( random( mypot+tapot ) > tapot )
	{
		message_vision(HIR"$N������������������ţ�\n"NOR, target);
                target->receive_damage("kee",mypot+(int)me->query("force_factor"));

		if( target->query_temp("weapon") )
		{
			obj = target->query_temp("weapon");
			if (!obj->is_newitem() && !obj->query("no_break")) {
				obj->unequip();
				obj->set("value", 0);
				message_vision(HIW "ֻ������ž����һ����$N���е�" + obj->name()+ HIW"�Ѿ���Ϊ���أ�\n" NOR, target);
				obj->set("name", "�ϵ���" + obj->query("name"));
				obj->set("weapon_prop", 0);
	            obj->set("armor_prop", 0);
	            obj->move(environment(target));
	            call_out("remove_broken_cloth",random(300)+60,obj);
			} else {
				message_vision(HIW "$Nֻ��������" + obj->name() + "�ѳֲ��������ַɳ���\n" NOR,
					target);
				obj->unequip();
				obj->move(environment(target));
				target->reset_action();
			}
		}
		if( sizeof(target->query_temp("armor")) )
		{
			inv = all_inventory(target);
			inv = filter(inv, (: $1->query("equipped") == "worn" :) );
			obj = inv[random(sizeof(inv))];
			if (!obj->is_newitem() && !obj->query("no_break")) {
				obj->unequip();
				obj->set("value", 0);
				obj->set("No_Wear", 1);
				message_vision(HIY"$N���ϵ�$n����ķ��飡\n"NOR, target,obj);
				obj->set("name", "�����"+obj->query("name"));
				obj->set("weapon_prop", 0);
	            obj->set("armor_prop", 0);
	            obj->move(environment(target));
	            call_out("remove_broken_cloth",random(300)+60,obj);
			} else {
				message_vision(HIW "$Nֻ�������ϵ�" + obj->name() + "�ѱ������ڵأ�\n" NOR,
					target);
				obj->unequip();
				obj->move(environment(target));
			}
	    }
		COMBAT_D->report_status(target);
	}
	else
	{
		message_vision(HIC"ȴ��$N�㿪�ˣ�\n"NOR, target);
	}

        me->add("force", -150);
	me->receive_damage("sen", 50);
        me->start_busy(1);
        me->set_temp("xingyun_end",time());
        return 1+random(5);
}

void remove_broken_cloth(object obj)
{
  if(obj && environment(obj)) {
    tell_object(environment(obj),
      "һ��΢�紵����"+obj->name()+"��ΪƬƬ��������ʧ�����ˡ�\n");
    destruct(obj);
  }
}
