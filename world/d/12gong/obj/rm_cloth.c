// by happ@YSZZ
#include <ansi.h>

#include <armor.h>

inherit CLOTH;

void create()
{
   set_name(HIY"������ʥ��"NOR, ({ "sheshou shengyi" }) );
   set_weight(3000);
   if( clonep() )
     set_default_object(__FILE__);
   else {
     set("unit", "��");
     set("material", "steel");
     set("armor_prop/armor",60);
     set("no_get","����ƽ�ʥ�²�������!\n");

   }
   set("special_effects", "��");  // emotion
   setup();
}

void init()
{
        object me = this_player();
        ::init();
         if(userp(me)&&!wizardp(me))
         {
       message_vision(HIY"�������ƽ�ʥ�¾�Ȼ�Զ����������ϵĻƽ����ֻ������ͻȻ��ǿ���յ����������ۣ�\n"NOR,me);
                call_out("greeting",5, me);
}

}
int greeting(object me)
{
   //  if( !me || !visible(me) || environment(me) != environment() ) return 0;
     if (me->query_temp("12gong/cike")=="done")
	{
		 message_vision(HIY"\n\n�ƽ������ָ������,ͻȻ�������!!!\n",me);
         message_vision(HIY"�㷴Ӧ����,���ƽ�����ض���.������������ƽ�ʥ��Ҳ�漴��ʧ��!\n"NOR,me);
		// me->add("eff_kee",-(query("eff_kee")/2));
		 me->receive_wound("kee",me->query("max_kee")/2+random(me->query("max_kee")/2)-me->query("max_kee")/10);

		 COMBAT_D->report_status(me);
        me->set("12gong/renma","done");
        me->add("12gong/number",1);
		destruct(this_object());
	}
           else
	{
			   message_vision(HIY"\n\n\n�ƽ������ת����ͨ��ɽ�򹬵�·��.\n",me);
			   message_vision(HIY"\nͻȻ,�ƽ���������˿���һ�����Ҷ���,����һ��ǿ���С���洩���˷���ͨ��ɽ�򹬵�����\n",me);
			   me->set("12gong/renma","done");
        me->add("12gong/number",1);
			   destruct(this_object());

	}
	        me->start_busy(3);
			message("chat",HIY+"\n\n���ƽ�ʮ������������˹(Aiolos):����������Զ�ػ�Ů��-�ŵ���!\n"NOR,users());
}
