#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me,string arg)
{
        object room,ob,shizhe;
        mapping baobiao_path;
        int value,level,number;

        if(me->is_busy()) return notify_fail("你正忙着呢！\n");
if (time()-(int)me->query_temp("digtime")<10) return notify_fail("别挖那么快!\n");
me->set_temp("digtime",time());
        room=environment(me);
        message_vision(HIY"正所谓人为财死，鸟为食亡，$N开始疯狂的挖掘是否有人埋了钱财在路上！\n"NOR,me);
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
        message_vision ("\n"+shizhe->query("name")+"突然跳了出来......,叫道：拿命来。\n",me);                
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

        	 message_vision(CYN"突然，火星四射，被$N挖到了一罐财宝！仔细一看，竟然是"+chinese_number(value)+"两金票！\n"NOR,me);
  //message_job( "三界神话："+me->query("name")+"挖到了"+chinese_number(value)+"两黄金！");
  message( "chat", HIY"\n【财神下凡】："+me->query("name")+"挖到了"+chinese_number(value)+"两金票！\n"NOR, users() );
        	 ob->set_amount(value);
        
        	 ob->move(room);
        	 }
        	 else{
        	 //ob=new("/d/quest/baoshi/baoshi");
			ob = new("/d/obj/newitem/baoshi/super_magic_stone");
	      	 if(!ob) return 1;
			 log_file("magic_stone", "诞生了一颗五彩宝石!\n");
        	 message_vision(CYN"突然，火星四射，被$N挖到了一罐财宝！仔细一看，竟然是一个"+ob->name()+"！\n"NOR,me);
     //message_job( "三界神话："+me->query("name")+"挖到了"+ob->name()+"！\n");
	 message( "chat", HIY"\n【财神下凡】："+me->query("name")+"挖到了"+ob->name()+"！\n"NOR, users() );
        	 ob->move(room);
        	 }
        me->delete_temp("digok");
        "/adm/daemons/ran_moneyd"->del_log(""+number);
        return 1;
                 }
}


