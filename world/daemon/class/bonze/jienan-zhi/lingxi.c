#include <ansi.h>

inherit SSERVER;
string* xuedao = ({
	"�İ�Ѩ",
	"�ز�Ѩ",
	"��ӭѨ",
	"Ͽ��Ѩ",
	"ͷάѨ",
	"�¹�Ѩ",
	"����Ѩ",
	"̫��Ѩ",
	"����Ѩ",
	"�ػ�Ѩ",
	"�ٳ�Ѩ",
	"�ٺ�Ѩ",
	"ͨ��Ѩ",
	"����Ѩ",
	"ӡ��Ѩ",
	"����Ѩ",
	"��ҺѨ",
	"����Ѩ",
	"����Ѩ",
	"�ٻ�Ѩ",
	"��̨Ѩ",
	"̫��Ѩ",
	"����Ѩ",
	"����Ѩ",
	"�βѨ",
	"����Ѩ",
});

int perform(object me, object target)
{
        
	object *inv, obj, obj1;
   	int damage,jiali;
	int i, mypot,tapot;
	string str,xuename;
	int cd = 5;
        object weapon;
       
        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С���Ϭָ����\n");

        if(!me->is_fighting(target))
                return notify_fail("����Ϭָ��ֻ����ս����ʹ�ã�\n");

        if((int)me->query("max_force") < 1000 )
                return notify_fail("�������������\n");
      	if(me->query("family/family_name") != "�Ϻ�����ɽ" )
                return notify_fail("�����Ķ�͵ѧ�����书��\n");

        if((int)me->query("force") < 600 )
                return notify_fail("����������㣡\n");

        if((int)me->query("sen") < 500 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");

	i=(int)me->query_skill("jienan-zhi",1);

        if( i < 120)
                return notify_fail("��Ľ���ָ���𻹲�����ʹ����һ�л������ѣ�\n");
	jiali = me->query("force_factor")+1;
	damage = me->query_skill("jienan-zhi", 1) + jiali;
	//if(damage > 500) damage = 500;
	
	if( me->query("lunhui_zhuanshi") )
		cd = 4;
        if( time()-(int)me->query_temp("lingxi_end") < cd )
                return notify_fail("��������Ϣ��˳��\n");
	message_vision(HIY"\n$N����𷨣���Ϭ���������۶ٿ���$N����$n��ʽ���������������ʳָ��յ��¡�\n"NOR,me,target);
	mypot = (int)me->query("combat_exp")/10000;
	tapot = (int)target->query("combat_exp")/12000;
       	
        if( random( mypot ) > tapot/3 || !living(target) ) 
	{       
             	xuename = xuedao[random(sizeof(xuedao))];
             	message_vision(HIY"\nֻ�������͡���һ������$N��ʳָ������$n��"+xuename+"�ϣ�$n��ʱ�������鶯�����á�\n"NOR,me,target);
              	target->start_busy(2+random(2));
		message_vision(HIY"\n$N��$n��Ȼ���У����һ�����ٵ��һ��ָ����\n"NOR,me, target);	
		message_vision(HIR"\nָ��͸��"+xuename+"��$n�������Ĵ���ͻ��$nʹ�಻����\n"NOR,me, target);
		target->receive_damage("kee", damage, me);
		target->receive_damage("sen", damage, me);
	        target->receive_wound("kee",damage,me);
         	target->receive_wound("sen",damage,me);
	 	COMBAT_D->report_status(target);
		COMBAT_D->report_sen_status(target);
	 	if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
         	{
         		str=target->name()+HIM"��"+me->name()+"��"+NOR+HIY"��Ϭָ��"+NOR+HIM"����"+xuename+"����ʱ�߿���Ѫ������";
    			message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
		}
	}	 
	else if( random(mypot+tapot) > tapot/2 )
	{
		message_vision(HIY"$Nʶ��������ƴ����ת�ķ���ͣ����ʽ������ԭ�ز��Ҷ�����\n"NOR, target);
		target->start_busy(2+random(3));
	        me->start_busy(1);
	}
	else
	{
		message_vision(HIC"$Nʶ����������æʹһ�����ӷ���㿪�ˣ�\n"NOR, target);
	        me->start_busy(2);
	}       
        me->add("force", -i/5);
	me->receive_damage("sen", i/5);
	me->set_temp("lingxi_end",time());
        return 1;
}




