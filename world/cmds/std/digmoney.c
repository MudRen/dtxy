#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me,string arg)
{
        object room,ob,shizhe;
        mapping baobiao_path;
        int value,level,number;

        if(me->is_busy()) return notify_fail("����æ���أ�\n");
if (time()-(int)me->query_temp("digtime")<10) return notify_fail("������ô��!\n");
me->set_temp("digtime",time());
        room=environment(me);
        message_vision(HIY"����ν��Ϊ��������Ϊʳ����$N��ʼ�����ھ��Ƿ���������Ǯ����·�ϣ�\n"NOR,me);
        me->receive_damage("kee",random(50)+100);

        if( !(baobiao_path=room->query("dig_money")) ) return 1;
        //if( !mapp(baobiao_path) || random(4) ) return 1;
		if( !mapp(baobiao_path)) return 1;

        if(!(value=baobiao_path["value"])) return 1;
        if(!(number=baobiao_path["number"])) return 1;
        if(!me->query_temp("digok"))
        {
        level = random(10);
        if (level<5) level=1;
        else if (level<8) level=2;
        else level=3;
        shizhe=new("/u/yekai/caishen/shizhe");
        shizhe->invocation(me, level);
        shizhe->move(room);
        message_vision ("\n"+shizhe->query("name")+"ͻȻ���˳���......,�е�����������\n",me);                
        shizhe->kill_ob(me);
        return 1;
           }
           else {
                                  
        room->delete("dig_money");      
        
        	if(random(50)>0)
        	 {
        	 ob=new("/obj/money/gold-cash");
       		 if(!ob) return 1;
                     value /= 4;

        	 message_vision(CYN"ͻȻ���������䣬��$N�ڵ���һ�޲Ʊ�����ϸһ������Ȼ��"+chinese_number(value)+"����Ʊ��\n"NOR,me);
  //message_job( "�����񻰣�"+me->query("name")+"�ڵ���"+chinese_number(value)+"���ƽ�");
  message( "chat", HIY"\n�������·�����"+me->query("name")+"�ڵ���"+chinese_number(value)+"����Ʊ��\n"NOR, users() );
        	 ob->set_amount(value);
        
        	 ob->move(room);
        	 }
        	 else{
        	 //ob=new("/d/quest/baoshi/baoshi");
			ob = new("/d/obj/newitem/baoshi/super_magic_stone");
	      	 if(!ob) return 1;
			 log_file("magic_stone", "������һ����ʱ�ʯ!\n");
        	 message_vision(CYN"ͻȻ���������䣬��$N�ڵ���һ�޲Ʊ�����ϸһ������Ȼ��һ��"+ob->name()+"��\n"NOR,me);
     //message_job( "�����񻰣�"+me->query("name")+"�ڵ���"+ob->name()+"��\n");
	 message( "chat", HIY"\n�������·�����"+me->query("name")+"�ڵ���"+ob->name()+"��\n"NOR, users() );
        	 ob->move(room);
        	 }
        me->delete_temp("digok");
        "/adm/daemons/ran_moneyd"->del_log(""+number);
        return 1;
                 }
}


