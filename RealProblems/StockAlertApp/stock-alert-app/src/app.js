const scrapeStockPrice = require('./scraper/stockScraper');
const { upperThreshold, lowerThreshold } = require('./config/thresholds');
const sendPhoneAlert = require('./alert/phoneAlert');
const sendEmailAlert = require('./alert/mailAlert');

const stockSymbol = 'MSFT'; // Example stock symbol
const checkInterval = 1000; // Check every 1 second
let isMessageSent = false;

const checkStockPrice = async () => {
    try {
        const currentPrice = await scrapeStockPrice(stockSymbol);
        console.log(`Current price of ${stockSymbol}: $${currentPrice}`);

        if (currentPrice > lowerThreshold) {
            if (!isMessageSent) {
                if (currentPrice > upperThreshold) {
                    sendPhoneAlert(`${stockSymbol} : $${currentPrice}, STRONG SELL signal!`);
                    sendEmailAlert(
                        `Stock Alert for ${stockSymbol}`,
                        `The stock price has risen above the upper threshold of $${upperThreshold}.
                        Current price: $${currentPrice}.
                        Consider STRONGLY selling your shares.`
                    )
                } else {
                    sendPhoneAlert(`${stockSymbol} : $${currentPrice}, SELL signal!`);
                    sendEmailAlert(
                        `Stock Alert for ${stockSymbol}`,
                        `The stock price has risen above the lower threshold of $${lowerThreshold}.
                        Current price: $${currentPrice}.
                        Consider selling your shares.`
                    )
                }
                isMessageSent = true;
            }
        } else {
            isMessageSent = false;
        }
    } catch (error) {
        console.error('Error fetching stock price:', error);
    }
};

setInterval(checkStockPrice, checkInterval);