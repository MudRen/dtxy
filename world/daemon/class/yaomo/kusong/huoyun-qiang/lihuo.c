
// �������
// yangwl 1/10/2001  ���Լ�����������

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        string msg,str;
        int extra;
        int ap,dp,chance;
        object weapon;
        extra = me->query_skill("huoyun-qiang",1);
        
        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "spear")
                        return notify_fail("��ʹ�õ��������ԡ�\n");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
               return notify_fail(HIR"��������ء�"NOR"ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        weapon = me->query_temp("weapon");
        if(extra < 180)
            return notify_fail("��Ļ���ǹ�����������죡\n");
     if(!wizardp(me) && me->query("family/family_name")!="���ƶ�")
           return notify_fail("��������ء�ֻ�л��ƶ����˲ſ����ã�\n");
     if(target->is_busy())
           return notify_fail("�Է��Ѿ���æ���ˣ��ͱ��Ż��˼��ˣ�\n");
        if(me->query("max_force") < 1500)
            return notify_fail("�����������������Ҫ��ǿ�ˣ�\n"); 
        if(me->query("force") < 1200)
            return notify_fail("���������������Ҫ��ǿ�ˣ�\n"); 
              
        
        //if(extra >= 400)  extra = 400;
        me->add("force", -extra/2);
        me->add_temp("apply/attack",extra/8);
        me->add_temp("apply/damage",extra/8);
        message_vision(HIR"\n$N����ǰָ��ǹ��ͻȻ���Ż�һ�㣬���顱��ը��һ���Ϻ�ɫ�Ļ��棬��
��ͨ��͸����ǹ��ȼ������������ˢ��������һ�������ӳ����������⣬
�������ؾ���һƬ����Ļ��࣬��$n��ͷ�ϸ�ȥ��"NOR,me,target);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        message_vision(HIR  "$Nȫ��������ţ�����ȽȽƮ����˫��ٿת���죡��" NOR,me,target);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
				message_vision(HIR  "$N����"+weapon->query("name")+ HIR"����������������ȼ���գ��ų���������ֱ�ӵ���׹⻪��" NOR,me,target);
        COMBAT_D->do_attack(me,target, me->query_temp("weapon"),TYPE_REGULAR,msg);
        me->add_temp("apply/attack",-extra/8);
        me->add_temp("apply/damage",-extra/8);
        if( me->query("lunhui_zhuanshi") > 3 )
        	me->start_busy(1);
        else
        	me->start_busy(2);
        message_vision(HIR"$N����"+weapon->query("name")+ HIR"һ�ӣ�һ�������������\n" NOR,me,target);
        message_vision(HIR"���ǣ�����������,�������ķ�,һ��ɱ��������,�����ǳ������⣡\n"NOR,me,target);
        		  ap = me->query("combat_exp")/1000;
			  dp = target->query("combat_exp")/1000*5/4;
			  if (dp < 1) 
			   		dp = 1;
			  chance = (int)(random(ap + dp) * 100 / dp);
			  if( chance > 55 ) 
   			  {
						message_vision(HIB"$n����������˳��棬��ʱ���ŵö������ã�\n" NOR,me,target);
						target->start_busy(3+random(3));
				}
				else if( chance > 33 ) 
				{
						message_vision(HIY"$n����ᶨ�����Է��ڷ���Ļ����Ӷ�������\n" NOR,me,target);
				}
				else
				{
						message_vision(HIC"$nһ����Ц����ȣ����ϻ������־��ܣ�\n" NOR,me,target);
						message_vision(HIC"������$nȫ������һ�У�����������Ļҷ�����\n" NOR,me,target);
						COMBAT_D->do_attack(target, me, target->query_temp("weapon"));
						if (me->query("eff_kee")<0 || (!living(me) && me->query("kee")<0))  
                       {str=me->name()+HIM"���Լ��ų���"NOR+HIR"��������"+HIM"�����ˣ���˵һ�������ûʣ�£�";
	                 message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	               }
				}
				 if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
                       {str=target->name()+HIM"��"+me->name()+"�ų���"NOR+HIR"��������"+HIM"�����ˣ���˵һ�������ûʣ�£�";
	                 message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	               }
        return 1;
}
