package org.playerbot.ai.domain;

import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.persistence.Column;
import javax.persistence.EmbeddedId;
import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;

@Entity
@Table(name = "log")
public class Log implements Serializable {
    private static final long serialVersionUID = 1L;

    public static final SimpleDateFormat DATE_FORMAT = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    private static class Key implements Serializable {
        private static final long serialVersionUID = 1L;
        
        public Key() {
            super();
        }

        @Column(name = "date")
        @Temporal(TemporalType.TIMESTAMP)
        private Date date;

        @Column(name = "number")
        private long number;
        
        @Override
        public int hashCode() {
            return new HashCodeBuilder().append(date).append(number).toHashCode();
        }

        @Override
        public boolean equals(Object obj) {
            if (this == obj)
                return true;

            if (obj == null || getClass() != obj.getClass())
                return false;

            return new EqualsBuilder().append(date, ((Key) obj).date).append(number, ((Key) obj).number).isEquals();
        }
    }
    
    @EmbeddedId
    private Key key = new Key();

    @Column(name = "bot")
    private String bot;

    @Column(name = "event")
    private String event;

    @Column(name = "text")
    private String text;

    @Column(name = "status")
    private String status;

    public Date getDate() {
        return key.date;
    }

    public void setDate(Date date) {
        key.date = date;
    }

    public long getNumber() {
        return key.number;
    }
    
    public void setNumber(long number) {
        key.number = number;
    }
    
    public String getBot() {
        return bot;
    }

    public void setBot(String bot) {
        this.bot = bot;
    }

    public String getEvent() {
        return event;
    }

    public void setEvent(String event) {
        this.event = event;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return String.format("%s.%d %s %s:%s", DATE_FORMAT.format(key.date), key.number, bot, event, text);
    }

    @Override
    public int hashCode() {
        return key.hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;

        if (obj == null || getClass() != obj.getClass())
            return false;

        return key.equals(((Log) obj).key);
    }

}
