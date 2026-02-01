require('dotenv').config();
const axios = require('axios');

async function scrapeStockPrice(symbol) {
  try {
    const apiKey = process.env.STOCK_API_KEY;
    const url = `https://finnhub.io/api/v1/quote?symbol=${symbol}&token=${apiKey}`;
    const response = await axios.get(url);
    return response?.data?.c;
  } catch (error) {
    console.error(`Error fetching stock data: ${error.message}`);
    throw error;
  }
}

module.exports = scrapeStockPrice;