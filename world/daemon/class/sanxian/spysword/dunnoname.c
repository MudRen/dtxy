//dunnoname������ �ǳ��� 
//created by mind 2001/2
// /daemon/class/sanxian/spysword/dunnoname.c

#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{       
        string str;
        int damage,wound;
        object weapon=me->query_temp("weapon");
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ�������� �ǳ�������\n");

        if(!me->is_fighting(target))
                return notify_fail("�������� �ǳ�����ֻ����ս����ʹ�ã�\n");
        
        if(me->query("family/family_name")!="����ɢ��")
                return notify_fail("�������͵���ľ��С������� �ǳ�������\n");
        
        if( (int)me->query("bellicosity") > 300 )
        return notify_fail("���ɱ��̫�أ������ϴ̿ͽ���Ҫ�塣\n");      
                
        if((int)me->query("max_force") < 500 )
                return notify_fail("�������������\n");

        if((int)me->query("force") < 500 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 300 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
        if((int)me->query_skill("binfen-steps", 1) < 50)
                return notify_fail("����ͷײ�����Ϊ��������ʹ����һ�л������ѣ�\n");
        if((int)me->query_skill("spysword", 1) < 50)
                return notify_fail("��Ĵ̿ͽ�����Ϊ��������ʹ����һ�л������ѣ�\n");
        if (me->query("betrayer") || me->query("betray/count"))
           return notify_fail("���Ķ����ߺ�������ɢ�ɵľ������ڡ�\n");
        if( me->query("lunhui_zhuanshi") )
        {
        	me->add_temp("apply/attack", me->query_skill("spysword", 1)/5);
        	me->add_temp("apply/damage", me->query_skill("binfen-steps", 1)/5);
        }
        target->add_temp("apply/dodge",-me->query_skill("spysword", 1)/2);
        target->add_temp("apply/parry",-me->query_skill("binfen-steps", 1)/2);

        message_vision(HIC"$N����̿ͽ�����Ҫּ�������� �ǳ�����������������������ʽ�ۼ���ѭ��$n��ȥ��\n"NOR,me,target);
        me->set("dunnoname", 8);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("dunnoname", 9);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("dunnoname", 10);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("dunnoname", 11);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("dunnoname", 12);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->set("dunnoname", 13);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
        
        me->delete("dunnoname");
        if( me->query("lunhui_zhuanshi") )
        {
        	me->add_temp("apply/attack", -me->query_skill("spysword", 1)/5);
        	me->add_temp("apply/damage", -me->query_skill("binfen-steps", 1)/5);
        }
        if( me->query("lunhui_zhuanshi") > 3 )
        	me->start_busy(1);
        else
        	me->start_busy(2);
        target->add_temp("apply/dodge",me->query_skill("spysword", 1)/2);
        target->add_temp("apply/parry",me->query_skill("binfen-steps", 1)/2);
        message_vision(HIC"$N���������ʹ�����У�������չ.\n"NOR,me,target);
        if( (target->query("eff_kee")<0 || !living(target)) && !random(5) )  
        {
str=target->name()+"��"+me->name()+"�ô̿ͽ����ľ���"+NOR+HIC"�������� �ǳ�����"+NOR+HIM"ɱ���ˡ���˵"+target->name()+HIM"��������֪������ʲô��ʽ֮�£�";
        message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
        }
        
        me->add("kee", -100);
        me->add("force", -250);
        me->add("sen",-100);
        return 1;
}

