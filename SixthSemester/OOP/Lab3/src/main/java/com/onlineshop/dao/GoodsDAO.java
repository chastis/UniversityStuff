package com.onlineshop.dao;

        import com.onlineshop.model.Goods;
        import org.springframework.data.jpa.repository.JpaRepository;
        import org.springframework.data.jpa.repository.Query;
        import org.springframework.stereotype.Repository;
        import org.springframework.transaction.annotation.Transactional;
        import java.util.List;

@Repository
@Transactional
public interface GoodsDAO extends JpaRepository<Goods, Integer> {
    @Query("SELECT g FROM  Goods g where g.idGoods=?1")
    List<Goods> getGoods(int var1);
}